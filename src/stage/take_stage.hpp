// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "stage.hpp"

namespace seq {

namespace {
struct TakeTransformation {

    explicit TakeTransformation(i64 howMany) : _howMany{howMany} { assert(_howMany >= 0); }

    // TODO: benchmark the 'Stage' against an equivalent 'TakeStage'
    template <typename Emitter, typename T>
    Status operator()(Emitter& emit, T&& arg) {
        if (_counter < _howMany) {
            _counter++;
            return emit(std::forward<T>(arg));
        }
        else {
            _counter = 0; // reset the counter, to allow restarting the pipeline where it left off
            return HALT;
        }
    }

    i64 const _howMany;
    i64 _counter{0};
};
}

template <typename T, typename F, typename S>
using TakeStage = Stage<T, TakeTransformation, S>;

template <typename T, typename S>
auto take(i64 howMany, S successor) {
    return Stage<T, TakeTransformation, S>{TakeTransformation{howMany}, successor};
}

}
