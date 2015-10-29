#include "net.hpp"
#include <iostream>

int main()
{
    std::cout << "Hello, I am a neural net!" << std::endl;

    net<float, sigmoid, 3, 1> nn;

    auto result = nn.run({0,0,0});
    for (auto& r : result)
        std::cout << r << " ";
    std::cout << endl;

    return 0;
}
