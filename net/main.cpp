#include "math.hpp"
#include "network.hpp"
#include "loaders.hpp"
#include "functions.hpp"

const uint epochs = 40;
const uint batch_size = 10;
const Scalar eta = 0.5;
const Scalar lambda = 0.0;
const std::vector<uint> shape = {20*20, 16*9, 16, 3};

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
/*
    auto training_data = txt_loader("training/data.txt");
    auto validation_data = txt_loader("validation/data.txt");
    auto testing_data = txt_loader("testing/data.txt");
*/
    auto training_data = bmp_loader("training");
    auto validation_data = bmp_loader("validation");
    auto testing_data = bmp_loader("testing");

    Network<Fast_sigmoid, Quadratic_cost> network(shape);
    //network.init(gen);
    network.init_2(gen);
    Statistics stats = network.sgd(training_data, epochs, batch_size, eta, lambda, gen, testing_data);

    std::ofstream acc("out/accurancy.csv");
    for (uint i = 0; i < epochs; ++i)
        acc << stats.training_accurancy[i] << "," << stats.evaluation_accurancy[i] << std::endl;

    std::ofstream cost("out/cost.csv");
    for (uint i = 0; i < epochs; ++i)
        cost << stats.training_cost[i] << "," << stats.evaluation_cost[i] << std::endl;

    return 0;
}