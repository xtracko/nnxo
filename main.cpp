#include "net.hpp"
#include <cmath>
#include <iostream>

/*
 * Functor of sigmoid function
 * s(t) = 1 / (1 + e^(-t))
 */
class Sigmoid {
public:
    using Type = float;
public:
    Type operator()(Type x) const
    {
        // NOTE: this is implementation of the fast sigmoid function
        return x / (1 + std::abs(x));
    }
};

using Net_type = Net<Sigmoid, 3, 1>;

int main()
{
    std::cout << "Hello, I am a neural net!" << std::endl;

    Net_type nn;

    typename Net_type::Out_type out = {};
    nn.run({0,0,0}, out);
    for (auto& r : out)
        std::cout << r << " ";
    std::cout << std::endl;

    return 0;
}
