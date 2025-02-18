// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "datatypes.hpp"

namespace seq {

template <typename Range>
struct RangeSink {
    using value_type = typename Range::value_type;

    RangeSink(Range& range) : _range{range} {}

    void receive(value_type&& value) {
        *(_range.begin() + _target_index) = std::forward<value_type>(value);
        ++_target_index;
    }

    Range& _range;
    mutable_i64 _target_index{0};
};

}
