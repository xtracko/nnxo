#include "net.hpp"
#include <iostream>

class Sigmoid {
public:
    using Type = float;
public:
    Type operator()(Type potencial) const
    {
        return 0;
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
