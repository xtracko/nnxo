#include "net.hpp"
#include <iostream>

class sigmoid {
public:
    using type = float;
public:
    type operator()(type potencial) const
    {
        return 0;
    }
};

using net_type = net<sigmoid, 3, 1>;

int main()
{
    std::cout << "Hello, I am a neural net!" << std::endl;

    net<sigmoid, 3, 1> nn;

    typename net_type::out_type out = {};
    nn.run({0,0,0}, out);
    for (auto& r : out)
        std::cout << r << " ";
    std::cout << std::endl;

    return 0;
}
