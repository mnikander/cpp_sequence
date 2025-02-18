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

template <typename T, typename S>
struct IotaSource {
    using Input = T;

    IotaSource(T init, S successor) : _index{init}, _successor{successor}, _emit{_successor} {}

    void yield(T const count = 1) {
        for(T i = 0; i < count; ++i) {
            _emit(std::forward<T>(_index));
            ++_index;
        }
    }

    T _index;
    S _successor;
    Emit<S> _emit;
};

template <typename T, typename S>
auto iota(T init, S successor) {
    return IotaSource<T, S>{init, successor};
}

template <typename S>
auto iota(S successor) {
    return IotaSource<int, S>{0, successor};
}

}
