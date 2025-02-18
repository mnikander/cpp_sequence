// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "stage.hpp"
#include "../datatypes.hpp"

namespace seq {

namespace {
template <typename F>
struct UnaryTransformation {

    explicit UnaryTransformation(F unaryFunction) : _function{unaryFunction} {}

    // We need a reference to the real instance of the emitter, held by the stage.
    // Since this instance is only available AFTER the constructor of the stage has finished, we
    // must pass it in every call. I am not sure if this has runtime performance repercussions.
    // To find out, I would need to benchmark the 'Stage' against an equivalent 'MapStage'.
    template <typename Emitter, typename T>
    Status operator()(Emitter& emit, T&& arg) {
        return emit(_function(std::forward<T>(arg)));
    }

    F _function;
};
}

template <typename T, typename F, typename S>
using MapStage = Stage<T, UnaryTransformation<F>, S>;

template <typename T, typename F, typename S>
auto map(F unaryFunction, S successor) {
    return Stage<T, UnaryTransformation<F>, S>{UnaryTransformation{unaryFunction}, successor};
}

}
