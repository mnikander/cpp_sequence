// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "stage.hpp"

namespace seq {

namespace {
template <typename F>
struct FilterTransformation {

    explicit FilterTransformation(F unaryPredicate) : _predicate{unaryPredicate} {}

    // TODO: benchmark the 'Stage' against an equivalent 'FilterStage'
    template <typename Emitter, typename T>
    void operator()(Emitter& emit, T&& arg) {
        if (_predicate(std::forward<T>(arg))) {
            emit(std::forward<T>(arg));
        }
    }

    F _predicate;
};
}

template <typename T, typename F, typename S>
using FilterStage = Stage<T, FilterTransformation<F>, S>;

template <typename T, typename F, typename S>
auto make_filter_stage(F unaryFunction, S successor) {
    return Stage<T, FilterTransformation<F>, S>{FilterTransformation{unaryFunction}, successor};
}

}
