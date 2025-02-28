// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {
namespace {

// Is there a better way to make iteration end, than using the limit in the 'yield' function?
// A later stage could communicate when to terminate the iteration, via a return value.
// This would complicate the design though, and make it similar to my prior design.
// Let's try it without back-communication, and see if we get a simpler design, which actually works.

template <typename T, typename S>
struct FromVectorImpl {
    using Input = T;

    FromVectorImpl(std::vector<T> & vector, S successor) : _vector{vector}, _successor{successor} {}
    FromVectorImpl(std::vector<T> const& vector, S successor) : _vector{vector}, _successor{successor} {}

    // yield runs a fixed number of times, unless it gets a HALT signal beforehand
    // yield can be called again, and it will continue where it left off last time, even if it stopped due to a HALT
    Status yield(uint64_t const count = 1u) {
        Status status = OK;
        for(uint64_t i = 0; i < count && _index != _vector.size() && status == OK; ++i) {
            status = _successor.receive(Input{_vector[_index]}); // copy the element to get an rvalue :(
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
            status = _successor.receive(Input{_vector[_index]}); // copy the element to get an rvalue :(
            ++_index;
        }
        status = HALT;
        return status;
    }

    uint64_t _index{0u};
    std::vector<T> const& _vector;
    S _successor;
};

template <typename T, typename S>
auto from_vector(std::vector<T> const& vector, S successor) {
    return FromVectorImpl<T, S>{vector, successor};
}

}
}
