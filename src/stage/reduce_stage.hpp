// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "stage.hpp"

namespace seq {

namespace {
template <typename F, typename T>
struct ReduceTransformation {

    explicit ReduceTransformation(F binaryFunction, T init) : _function{binaryFunction}, _accumulator{init} {}

    // TODO: benchmark this against an equivalent 'Stage', to check if this transformation introduces overhead
    template <typename Emitter>
    void operator()(Emitter& emit, T&& arg) {
        _accumulator = _function(_accumulator, std::forward<T>(arg));
        emit(std::forward<T>(_accumulator));
    }

    F _function;
    T _accumulator;
};
}

template <typename T, typename F, typename S>
using ReduceStage = Stage<T, ReduceTransformation<F, T>, S>;

template <typename T, typename F, typename S>
auto make_reduce_stage(F binaryFunction, T init, S successor) {
    return Stage<T, ReduceTransformation<F, T>, S>{ReduceTransformation<F, T>{binaryFunction, init}, successor};
}

}
