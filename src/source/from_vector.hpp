// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {
namespace {

// Is there a better way to make iteration end, than using the limit in the 'yield' function?
// A later stage could communicate when to terminate the iteration, via a return value.
// This would complicate the design though, and make it similar to my prior design.
// Let's try it without back-communication, and see if we get a simpler design, which actually works.

using V = std::vector<i64>;

template </*typename V,*/ typename S>
struct FromVectorImpl {
    using Input = typename V::value_type;

    FromVectorImpl(V & vector, S successor) : _vector{vector}, _successor{successor} {}

    // yield runs a fixed number of times, unless it gets a HALT signal beforehand
    // yield can be called again, and it will continue where it left off last time, even if it stopped due to a HALT
    Status yield(uint64_t const count = 1) {
        Status status = OK;
        for(uint64_t i = 0; i < count && _index != _vector.size() && status == OK; ++i) {
            status = _successor.receive(std::move(_vector[_index]));
            ++_index;
        }
        if (_index == _vector.size()) {
            status = HALT;
        }
        return status;
    }

    Status run() {
        Status status = OK;
        while(_index != _vector.size() && status == OK) {
            status = _successor.receive(std::move(_vector[_index]));
            ++_index;
        }
        if (_index == _vector.size()) {
            status = HALT;
        }
        return status;
    }

    uint64_t _index{0u};
    V & _vector;
    S _successor;
};

template <typename S>
auto from_vector(std::vector<i64> & vector, S successor) {
    return FromVectorImpl<S>{vector, successor};
}

}
}
