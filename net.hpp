#pragma once

using uint = unsigned int;

template <class T, class Func, uint In>
class neuron {
    using type = T;
    using array_type = type[In];

    type _bias;
    array_type _weights;
public:
    type run(const array_type& inputs) const
    {
        Func func;
        return func(compute_potencial(inputs));
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

template <class T, class Func, uint In, uint Size>
class layer {
    using neuron_type = neuron<T, Func, In>;
    using in_type = typename neuron_type::array_type;
    using out_type = decltype(neuron_type::run)[Size];

    neuron_type _neurons[Size];
public:
    out_type run(const in_type& inputs) const
    {
        out_type outputs;
        for (uint i = 0; i < Size; ++i)
            outputs[i] = _neurons[i].run(inputs);
        return outputs;
    }
};

template <class T, class Func, uint In, uint N, uint... Ns>
class net {
    using head_type = layer<T, Func, In, N>;

    head_type _head;
    net<T, N, Ns...> _tail;
public:
    auto run(const head_type::in_type& inputs) const
    {
        auto outputs = _head.run(inputs);
        return _tail.run(outputs);
    }
};

template <class T, class Func, uint In, uint N>
class net<T, Func, In, N> {
    using head_type = layer<T, Func, In, N>;

    head_type _head;
public:
    auto run(const head_type::in_array& inputs) const
    {
        return _head.run(inputs);
    }
};
