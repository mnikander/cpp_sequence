// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {
namespace {

template <typename I, typename F, typename A, typename S>
struct ReduceImpl {
    using Input  = I;

    explicit ReduceImpl(F binaryFunction, A init, S successor) : _function{binaryFunction}, _accumulator{init}, _successor{successor} {}

    Status receive(I&& value) {
        _accumulator = _function(std::move(_accumulator), std::forward<I>(value));
        return _successor.receive(std::forward<A>(_accumulator));
    }

    F _function;
    A _accumulator;
    S _successor;
};
}

template <typename I, typename F, typename A, typename S>
auto reduce(F binaryFunction, A init, S successor) {
    return ReduceImpl<I, F, A, S>{binaryFunction, init, successor};
}

}
