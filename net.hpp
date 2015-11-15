#pragma once

using uint = unsigned int;

template <class F, uint In>
class Neuron {
public:
    using Function = F;
    using Type = typename F::Type;
    using Array_type = Type[In];
private:
    Function _func;
    Type _bias;
    Array_type _weights;
public:
    Type run(const Array_type& inputs) const
    {
        return _func(compute_potencial(inputs));
    }
protected:
    Type compute_potencial(const Array_type& inputs) const
    {
        // NOTE: computing sum of floats iteratively like this could cause rounding error
        Type potencial = _bias;
        for (uint i = 0; i < In; ++i)
            potencial += _weights[i] * inputs[i];
        return potencial;
    }
};

template <class F, uint In, uint Size>
class Layer {
public:
    using Neuron_type = Neuron<F, In>;
    using In_type = typename Neuron_type::Array_type;
    using Out_type = typename Neuron_type::Type[Size];
private:
    Neuron_type _neurons[Size];
public:
    void run(const In_type& ins, Out_type& outs) const
    {
        for (uint i = 0; i < Size; ++i)
            outs[i] = _neurons[i].run(ins);
    }
};

template <class F, uint In, uint N, uint... Ns>
class Net {
    using Head_type = Layer<F, In, N>;
    using Tail_type = Net<F, N, Ns...>;
public:
    using In_type = typename Head_type::In_type;
    using Out_type = typename Tail_type::Out_type;
private:
    Head_type _head;
    Tail_type _tail;
public:
    void run(const In_type& ins, Out_type& outs) const
    {
        Head_type::Out_type tmp;

        _head.run(ins, tmp);
        _tail.run(tmp, outs);
    }
};

template <class F, uint In, uint N>
class Net<F, In, N> {
    using Head_type = Layer<F, In, N>;
public:
    using In_type = typename Head_type::In_type;
    using Out_type = typename Head_type::Out_type;
private:
    Head_type _head;
public:
    void run(const In_type& ins, Out_type& outs) const
    {
        _head.run(ins, outs);
    }
};
