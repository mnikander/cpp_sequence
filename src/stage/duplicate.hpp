// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {
namespace {

template <typename I, typename S>
struct DuplicateImpl {
    using Input = I;

    explicit DuplicateImpl(i64 howOften, S successor) : _howOften{howOften}, _successor{successor} {}

    Status receive(Input&& value) {
        Status status = OK;
        i64 count = 0;
        while (count < _howOften && status == OK) {
            status = _successor.receive(std::forward<Input>(value)); // do nothing, just forward the input to the next stage
            ++count;
        }
        return status;
    }

    i64 _howOften;
    S _successor;
};
}

template <typename I, typename S>
auto duplicate(i64 howOften, S successor) {
    assert(howOften >= 1);
    return DuplicateImpl<I, S>{howOften, successor};
}

template <typename I, typename S>
auto duplicate(S successor) {
    return DuplicateImpl<I, S>{2, successor};
}

}
