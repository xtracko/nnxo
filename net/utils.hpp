#pragma once

#include "math.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

struct Model {
    Vector x;
    Vector y;

    Model(uint in, uint out)
        : x(in)
        , y(out)
    {}
};

using Data = std::vector<Model>;

struct Batch {
    Matrix x;
    Matrix y;

    Batch(uint in, uint out, uint n)
        : x(in, n)
        , y(out, n)
    {}

    Batch (Batch const&) = default;

    uint size() const { return x.cols(); }
};

template <class It>
Batch create_batch(It begin, uint n)
{
    Batch batch(begin->x.rows(), begin->y.rows(), n);
    for (uint i = 0; i < n; ++i, ++begin) {
        for (uint j = 0; j < begin->x.rows(); ++j)
            batch.x.at(j, i) = begin->x.at(j);
        for (uint j = 0; j < begin->y.rows(); ++j)
            batch.y.at(j, i) = begin->y.at(j);
    }
    return batch;
}

template <class T>
std::vector<Batch> prepare_batches(Data & data, uint batch_size, T & gen)
{
    std::shuffle(data.begin(), data.end(), gen);

    std::vector<Batch> batches;

    batches.reserve(data.size());
    auto it = data.cbegin();
    for (; it + batch_size < data.cend(); it += batch_size)
        batches.emplace_back( create_batch(it, batch_size) );
    batches.emplace_back( create_batch(it, data.cend() - it) );

    return batches;
}

struct Statistics {
    std::vector<double> training_cost;
    std::vector<double> evaluation_cost;

    std::vector<double> training_accurancy;
    std::vector<double> evaluation_accurancy;
};
