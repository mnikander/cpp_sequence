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

template <typename I, typename S>
struct FromIotaImpl {
    using Input = I;

    FromIotaImpl(I init, S successor) : _index{init}, _successor{successor} {}

    // yield runs a fixed number of times, unless it gets a HALT signal beforehand
    // yield can be called again, and it will continue where it left off last time, even if it stopped due to a HALT
    Status yield(I const count = 1) {
        assert(count >= 0);
        Status status = OK;
        for(I i = 0; i < count && status == OK; ++i) {
            status = _successor.receive(std::forward<I>(_index));
            ++_index;
        }
        return status;
    }

    Status run() {
        Status status = OK;
        while(status == OK) {
            status = _successor.receive(std::forward<I>(_index));
            if(status == OK) {
                ++_index;
            }
        }
        return status;
    }

    I _index;
    S _successor;
};

template <typename I, typename S>
auto from_iota(I init, S successor) {
    return FromIotaImpl<I, S>{init, successor};
}

template <typename S>
auto from_iota(S successor) {
    return FromIotaImpl<int, S>{0, successor};
}

}
}
