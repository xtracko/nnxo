#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "network.hpp"

void save_statistics(const Statistics& stats, const std::string& folder)
{
    uint epochs = stats.training_accurancy.size();

    std::ofstream acc(folder + "/accurancy.csv");
    for (uint i = 0; i < epochs; ++i)
        acc << stats.training_accurancy[i] << "," << stats.evaluation_accurancy[i] << std::endl;

    std::ofstream cost(folder + "/cost.csv");
    for (uint i = 0; i < epochs; ++i)
        cost << stats.training_cost[i] << "," << stats.evaluation_cost[i] << std::endl;

    std::ofstream tr_conf(folder + "/training_confusion.txt");
    for (uint i = 0; i < epochs; ++i)
        tr_conf << "epoch: " << i << std::endl << stats.training_confusions[i] << std::endl;


    std::ofstream ev_conf(folder + "/validation_confusion.txt");
    for (uint i = 0; i < epochs; ++i)
        ev_conf << "epoch: " << i << std::endl << stats.evaluation_confusions[i] << std::endl;
}
