#pragma once

#include "math.hpp"
#include <random>
#include <algorithm>
#include <iostream>

struct Model {
    Vector x;
    Vector y;

    Model(uint in, uint out)
        : x(in)
        , y(out)
    {}
};

struct Batch {
    Matrix x;
    Matrix y;

    Batch(uint in, uint out, uint n)
        : x(in, n)
        , y(out, n)
    {}
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

struct Layer {
    Matrix w;
    Vector b;

    Layer() = default;

    Layer(uint in, uint out)
        : w(out, in)
        , b(out)
    {}

    uint in() const { return w.cols(); }
    uint out() const { return w.rows(); }

    Vector compute_potencial(const Vector& x) const { return w * x + b; }
    Matrix compute_potencial(const Matrix& xs) const { return w * xs + b; }
};

template <class Func>
class Network {
    std::vector<Layer> _ls;
public:
    Network(std::vector<uint>&& sizes)
    {
        assert(sizes.size() > 1);

        for (uint i = 0; i < sizes.size() - 1; ++i)
            _ls.emplace_back(sizes[i], sizes[i + 1]);
        init();
    }

public:
    Vector evaluate(Vector x) const
    {
        for (auto& layer : _ls)
            x = layer.compute_potencial(x).map(Func::root);
        return x;
    }

    Matrix evaluate(Matrix xs) const
    {
        for (auto& layer : _ls)
            xs = layer.compute_potencial(xs).map(Func::root);
        return xs;
    }

    void sgd(std::vector<Model> set, const uint epochs, const uint batch_size, const Scalar eta)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (uint i = 0; i < epochs; i++) {
            std::shuffle(set.begin(), set.end(), gen);

            std::vector<Batch> batches;

            auto it = set.cbegin();
            for (; it + batch_size < set.cend(); it += batch_size)
                batches.emplace_back( create_batch(it, batch_size) );
            batches.emplace_back( create_batch(it, set.cend() - it) );

            for (auto& batch : batches)
                update_batch(batch.x, batch.y, eta);
            std::cout << "epoch " << i << " complete" << std::endl;
        }
    }

protected:
    void update_batch(const Matrix& x, const Matrix& y, Scalar eta)
    {
        assert(x.cols() == y.cols());

        auto nabla = backprop(x, y);
        auto ratio = eta / x.cols();

        for (uint i = 0; i < _ls.size(); ++i) {
            _ls[i].b = _ls[i].b - ratio * nabla[i].b;
            _ls[i].w = _ls[i].w - ratio * nabla[i].w;
        }
    }

    std::vector<Layer> backprop(const Matrix& x, const Matrix& y) const
    {
        std::vector<Layer> nabla(_ls.size());

        std::vector<Matrix> zs; // potencials
        std::vector<Matrix> as; // activations

        // feedforward
        as.emplace_back(x);
        for (auto& layer : _ls) {
            zs.emplace_back(layer.compute_potencial(as.back()));
            as.emplace_back(zs.back().map(Func::root));
        }

        // backward pass
        auto rzs = zs.rbegin();
        auto ras = as.rbegin();
        auto rnabla = nabla.rbegin();
        auto rls = _ls.rbegin();

        auto delta = hadamard_product(ras[0] - y,  rzs[0].map(Func::derivative));
        rnabla[0].b = sum_columns(delta);
        rnabla[0].w = delta * ras[1].transpose();

        for (uint i = 1; i < _ls.size(); ++i) {
            const auto sp = rzs[i].map(Func::derivative);
            delta = (rls[i - 1].w.transpose() * delta) * sp;

            rnabla[i].b = sum_columns(delta);
            rnabla[i].w = delta * ras[i].transpose();
        }
        return nabla;
    }
protected:
    void init()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<Scalar> dist;

        for (auto& layer : _ls) {
            for (uint i = 0; i < layer.b.rows(); ++i)
                layer.b.at(i) = dist(gen);

            for (uint i = 0; i < layer.w.rows(); ++i)
                for (uint j = 0; j < layer.w.cols(); ++j)
                    layer.w.at(i, j) = dist(gen);
        }
    }
};
