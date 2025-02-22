// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {
namespace {

template <typename I, typename F, typename S>
struct FilterImpl {
    using Input  = I;

    explicit FilterImpl(F unaryPredicate, S successor) : _predicate{unaryPredicate}, _successor{successor} {}

    Status receive(Input&& value) {
        if (_predicate(std::forward<Input>(value))) {
            return _successor.receive(std::forward<Input>(value)); // do nothing, just forward the input to the next stage
        }
        else {
            return OK;
        }
    }

    F _predicate;
    S _successor;
};

template <typename I, typename F, typename S>
auto filter(F unaryFunction, S successor) {
    return FilterImpl<I, F, S>{unaryFunction, successor};
}

}
}
