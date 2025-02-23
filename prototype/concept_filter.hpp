// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../src/datatypes.hpp"

namespace proto {
namespace con {

namespace {
template <typename I, typename F, typename S>
struct FilterImpl {

    explicit FilterImpl(F unaryPredicate, S successor) : _predicate{unaryPredicate}, _successor{successor} {}

    Status operator()(I&& arg) {
        if (_predicate(std::forward<I>(arg))) {
            return _successor.receive(std::forward<I>(arg));
        }
        else {
            return OK;
        }
    }

    F _predicate;
    S _successor;
};
}

template <typename I, typename F, typename S>
auto filter(F unaryFunction, S successor) {
    return Stage<I, FilterImpl<F>, S>{FilterImpl{unaryFunction}, successor};
}

}
}
