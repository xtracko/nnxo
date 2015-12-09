#include "math.hpp"
#include "network.hpp"
#include "loaders.hpp"
#include "functions.hpp"

const uint variants = 1;
const uint epochs = 500;
const uint batch_size = 10;
const Scalar eta = 0.01;
const Scalar lambda = 0.0;
const std::vector<uint> shape = {11*11, 3};

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
/*
    auto training_data = txt_loader("training/data.txt");
    auto validation_data = txt_loader("validation/data.txt");
    auto testing_data = txt_loader("testing/data.txt");
*/

    auto training_data = bmp_loader("training", variants);
    auto validation_data = bmp_loader("validation", variants);
    auto testing_data = bmp_loader("testing", variants);


    Network<Fast_sigmoid, Quadratic_cost> network(shape);
    //network.init(gen);
    network.init_2(gen);
    Statistics stats = network.sgd(training_data, epochs, batch_size, eta, lambda, gen, validation_data);

    std::ofstream acc("out/accurancy.csv");
    for (uint i = 0; i < epochs; ++i)
        acc << stats.training_accurancy[i] << "," << stats.evaluation_accurancy[i] << std::endl;

    std::ofstream cost("out/cost.csv");
    for (uint i = 0; i < epochs; ++i)
        cost << stats.training_cost[i] << "," << stats.evaluation_cost[i] << std::endl;

    std::ofstream tr_conf("out/training_conf.txt");
    for (uint i = 0; i < epochs; ++i)
        tr_conf << "epoch: " << i << std::endl << stats.training_confusions[i] << std::endl;


    std::ofstream ev_conf("out/validation_conf.txt");
    for (uint i = 0; i < epochs; ++i)
        ev_conf << "epoch: " << i << std::endl << stats.evaluation_confusions[i] << std::endl;

    //results

    std::ofstream te_conf("out/testing_conf.txt");
    te_conf << network.confusion(testing_data);

    std::ofstream te_acc("out/testing_acc.txt");
    te_acc << network.accurancy(testing_data);

    return 0;
}
