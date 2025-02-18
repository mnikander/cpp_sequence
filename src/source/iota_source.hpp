// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
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

    // yield runs a fixed number of times, unless it gets a HALT signal beforehand
    // yield can be called again, and it will continue where it left off last time, even if it stopped due to a HALT
    Status yield(T const count = 1) {
        assert(count >= 0);
        Status status = OK;
        for(T i = 0; i < count && status == OK; ++i) {
            status = _emit(std::forward<T>(_index));
            ++_index;
        }
        return status;
    }

    Status run() {
        Status status = OK;
        while(status == OK) {
            status = _emit(std::forward<T>(_index));
            if(status == OK) {
                ++_index;
            }
        }
        return status;
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
