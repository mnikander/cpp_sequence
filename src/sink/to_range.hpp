// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {

template <typename Range>
struct RangeSink {
    using Input = typename Range::value_type;

    RangeSink(Range& range) : _range{range} {}

    Status receive(Input&& value) {
        *(_range.begin() + _target_index) = std::forward<Input>(value);
        ++_target_index;
        return OK;
    }

    Range& _range;
    i64 _target_index{0};
};

template <typename R>
auto to_range(R& range) {
    return RangeSink<R>{range};
}

}
