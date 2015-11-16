#include "net.hpp"
#include <cmath>
#include <iomanip>
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
    typename Net_type::In_type ins = {0, 0, 0};
    typename Net_type::Out_type outs = {};

    nn.run({0,0,0}, outs);

    // Print the otuput layer
    std::cout << std::fixed << std::setprecision(3);
    for (auto val : outs)
        std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}
