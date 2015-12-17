#pragma once

#include "math.hpp"
#include "utils.hpp"
#include <random>
#include <iostream>

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

template <class Func, template <class> class Cost_t>
class Network {
    using Cost = Cost_t<Func>;

    std::vector<Layer> _layers;
public:
    Network(std::vector<uint> shape)
    {
        assert(shape.size() > 1);

        for (uint i = 0; i < shape.size() - 1; ++i)
            _layers.emplace_back(shape[i], shape[i + 1]);
    }
public:
    template <class T>
    void init(T gen)
    {
        std::normal_distribution<Scalar> dist;

        for (auto& layer : _layers) {
            for (uint i = 0; i < layer.b.rows(); ++i)
                layer.b.at(i) = dist(gen);

            for (uint i = 0; i < layer.w.rows(); ++i)
                for (uint j = 0; j < layer.w.cols(); ++j)
                    layer.w.at(i, j) = dist(gen);
        }
    }

    template <class T>
    void init_2(T gen)
    {
        std::normal_distribution<Scalar> dist;

        for (auto& layer : _layers) {
            for (uint i = 0; i < layer.b.rows(); ++i)
                layer.b.at(i) = dist(gen);

            for (uint i = 0; i < layer.w.rows(); ++i)
                for (uint j = 0; j < layer.w.cols(); ++j)
                    layer.w.at(i, j) = dist(gen) / std::sqrt(layer.in());
        }
    }

    double accurancy(Data const& data) const
    {
        double sum = 0;
        for (auto& model : data) {
            const auto a = feedforward(model.x);
            sum += static_cast<uint>(max_elem(a) == max_elem(model.y));
        }
        return sum / data.size();
    }

    double total_cost(Data const& data, Scalar lambda) const
    {
        double cost = 0;
        for (auto& model : data) {
            const auto a = feedforward(model.x);
            cost += Cost::fn(a, model.y) / data.size();
        }

        double sum_w = 0;
        for (auto & layer : _layers) {
            const auto nw = layer.w.norm();
            sum_w += nw * nw;
        }

        cost += .5 * (lambda / data.size()) * sum_w;
        return cost;
    }

    template <class T>
    Statistics sgd(Data & training_data, uint epochs, uint batch_size, Scalar eta, Scalar lambda, T & gen, Data & evaluation_data)
    {
        uint n = training_data.size();

        Statistics stats;

        for (uint e = 0; e < epochs; ++e) {
            const auto batches = prepare_batches(training_data, batch_size, gen);

            for (auto& batch : batches)
                update_batch(batch, eta, lambda, n);
            std::cout << "epoch " << e << " from " << epochs << " complete" << std::endl;

            stats.training_accurancy.emplace_back(accurancy(training_data));
            stats.training_cost.emplace_back(total_cost(training_data, lambda));

            stats.evaluation_accurancy.emplace_back(accurancy(evaluation_data));
            stats.evaluation_cost.emplace_back(total_cost(evaluation_data, lambda));

            stats.training_confusions.emplace_back(confusion(training_data));
            stats.evaluation_confusions.emplace_back(confusion(evaluation_data));
        }
        return stats;
    }

    Matrix confusion(const Data& data)
    {
        Matrix m(3,3);
        for (auto& model : data) {
            Vector out = feedforward(model.x);
            m.at(max_elem(out), max_elem(model.y)) += 1;
/*
            if (max_elem(out) == 2 && max_elem(model.y) == 0)
                std::cout << "20    " << model.x << std::endl;
            if (max_elem(out) == 0 && max_elem(model.y) == 2)
                std::cout << "02    " << model.x << std::endl;
*/
        }
        return m;
    }

protected:
    Vector feedforward(Vector a) const
    {
        for (auto& layer : _layers)
            a = layer.compute_potencial(a).map(Func::root);
        return a;
    }

    void update_batch(Batch const& batch, Scalar eta, Scalar lambda, uint n)
    {
        auto nabla = backprop(batch);
        auto ratio = eta / batch.size();

        for (uint i = 0; i < _layers.size(); ++i) {
            _layers[i].b = _layers[i].b - ratio * nabla[i].b;
            _layers[i].w = (1 - eta * (lambda / n)) * _layers[i].w - ratio * nabla[i].w;
        }
    }

    std::vector<Layer> backprop(Batch const& batch) const
    {
        std::vector<Layer> nabla(_layers.size());

        std::vector<Matrix> zs; // potencials
        std::vector<Matrix> as; // activations

        // feedforward
        as.emplace_back(batch.x);
        for (auto& layer : _layers) {
            zs.emplace_back(layer.compute_potencial(as.back()));
            as.emplace_back(zs.back().map(Func::root));
        }

        // backward pass
        auto rzs = zs.rbegin();
        auto ras = as.rbegin();
        auto rnabla = nabla.rbegin();
        auto rls = _layers.rbegin();

        auto delta = Cost::delta(rzs[0], ras[0], batch.y);
        rnabla[0].b = sum_columns(delta);
        rnabla[0].w = delta * ras[1].transpose();

        for (uint i = 1; i < _layers.size(); ++i) {
            const auto sp = rzs[i].map(Func::derivative);
            delta = hadamard_product(rls[i - 1].w.transpose() * delta, sp);

            rnabla[i].b = sum_columns(delta);
            rnabla[i].w = delta * ras[i + 1].transpose();
        }
        return nabla;
    }
};
