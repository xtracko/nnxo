#include "network.hpp"
#include "serialization.hpp"
#include <cmath>
#include <ios>
#include <iostream>
#include <string>
#include <fstream>

struct Fast_sigmoid {
    static Scalar root(const Scalar x)
    {
        return x / (1 + std::abs(x));
    }

    static Scalar derivative(const Scalar x)
    {
        const Scalar tmp = 1 + std::abs(x);
        return Scalar(1) / (tmp * tmp);
    }
};

std::vector<Model> txt_loader(const std::string& file)
{
    std::vector<Model> set;
    std::ifstream fin(file);
    std::cout << "loading [" << file << "]..." << std::endl;

    Model model(9, 3);
    while (fin.good()) {
        for (uint i = 0; i < 9; ++i)
            fin >> model.x.at(i);
        fin >> ",";
        for (uint i = 0; i < 3; ++i)
            fin >> model.y.at(i);

        set.emplace_back(model);
    }

    std::cout << "loading of " << set.size() << " models completed" << std::endl;
    return set;
}

int main()
{
    std::cin.exceptions(std::istream::failbit);

    std::cout << "Hello, I am a neural net!" << std::endl << std::endl;

    auto training_set = txt_loader("training.txt");
    auto testing_set = txt_loader("testing.txt");
    //auto validation_set = txt_loader("validation.txt");

    Network<Fast_sigmoid> net({9,3});
    net.sgd(training_set, 1000, 10, .01);

    for (const auto& model : testing_set) {
        std::cout << net.evaluate(model.x) << std::endl;
        std::cout << model.y << std::endl;
        std::cout <<std::endl;
    }

    return 0;
}
