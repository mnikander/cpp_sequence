// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <iterator>
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {
namespace {

// Is there a better way to make iteration end, than using the limit in the 'yield' function?
// A later stage could communicate when to terminate the iteration, via a return value.
// This would complicate the design though, and make it similar to my prior design.
// Let's try it without back-communication, and see if we get a simpler design, which actually works.

template <typename I, typename S>
struct FromRangeImpl {
    using Input = typename std::iterator_traits<I>::value_type;

    FromRangeImpl(I first, I last, S successor) : _first{first}, _current{first}, _last{last}, _successor{successor} {}

    // yield runs a fixed number of times, unless it gets a HALT signal beforehand
    // yield can be called again, and it will continue where it left off last time, even if it stopped due to a HALT
    Status yield(i64 const count = 1) {
        assert(count >= 0);
        Status status = OK;
        for(i64 i = 0; i < count && _current != _last && status == OK; ++i) {
            status = _successor.receive(*_current);
            ++_current;
        }
        if (_current != _last) {
            status = HALT;
        }
        return status;
    }

    Status run() {
        Status status = OK;
        while(_current != _last && status == OK) {
            status = _successor.receive(*_current);
            ++_current;
        }
        if (_current != _last) {
            status = HALT;
        }
        return status;
    }

    I _first;
    I _current;
    I _last;
    S _successor;
};

template <typename I, typename S>
auto from_range(I first, I last, S successor) {
    return FromRangeImpl<I, S>{first, last, successor};
}

template <typename R, typename S>
auto from_range(R range, S successor) {
    return FromRangeImpl<typename R::const_iterator, S>{range.cbegin(), range.cend(), successor};
}

}
}
