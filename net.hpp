#pragma once

using uint = unsigned int;

template <class F, uint In>
class neuron {
public:
    using function = F;
    using type = typename F::type;
    using array_type = type[In];
private:
    function _func;
    type _bias;
    array_type _weights;
public:
    type run(const array_type& inputs) const
    {
        return _func(compute_potencial(inputs));
    }
protected:
    type compute_potencial(const array_type& inputs) const
    {
        // NOTE: computing sum of floats iteratively like this could cause rounding error
        type potencial = _bias;
        for (uint i = 0; i < In; ++i)
            potencial += _weights[i] * inputs[i];
        return potencial;
    }
};

template <class F, uint In, uint Size>
class layer {
public:
    using neuron_type = neuron<F, In>;
    using in_type = typename neuron_type::array_type;
    using out_type = typename neuron_type::type[Size];
private:
    neuron_type _neurons[Size];
public:
    void run(const in_type& ins, out_type& outs) const
    {
        for (uint i = 0; i < Size; ++i)
            outs[i] = _neurons[i].run(ins);
    }
};

template <class F, uint In, uint N, uint... Ns>
class net {
    using head_type = layer<F, In, N>;
    using tail_type = net<F, N, Ns...>;
public:
    using in_type = typename head_type::in_type;
    using out_type = typename tail_type::out_type;
private:
    head_type _head;
    tail_type _tail;
public:
    void run(const in_type& ins, out_type& outs) const
    {
        head_type::out_type tmp;

        _head.run(ins, tmp);
        _tail.run(tmp, outs);
    }
};

template <class F, uint In, uint N>
class net<F, In, N> {
    using head_type = layer<F, In, N>;
public:
    using in_type = typename head_type::in_type;
    using out_type = typename head_type::out_type;
private:
    head_type _head;
public:
    void run(const in_type& ins, out_type& outs) const
    {
        _head.run(ins, outs);
    }
};
