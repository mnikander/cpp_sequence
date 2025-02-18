// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../datatypes.hpp"
#include "../emit.hpp"

namespace seq {

// Is there a better way to make iteration end, than using the limit in the 'yield' function?
// A later stage could communicate when to terminate the iteration, via a return value.
// This would complicate the design though, and make it similar to my prior design.
// Let's try it without back-communication, and see if we get a simpler design, which actually works.

template <typename S>
struct IotaSource {
    using Input = i64;

    IotaSource(S successor) : _successor{successor}, _emit{_successor} {}

    void yield(i64 const count = 1) {
        for(i64 i = 0; i < count; ++i) {
            _emit(std::forward<i64>(_index));
            ++_index;
        }
    }

    S _successor;
    Emit<S> _emit;
    i64 _index{0};
};

template <typename S>
auto iota(S successor) {
    return IotaSource<S>{successor};
}

}
