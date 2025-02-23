// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "../src/datatypes.hpp"

namespace seq {
namespace proto {
namespace crtp {

template <typename I, typename S, typename Derived>
struct BaseStage {
    using Input     = I;
    using Successor = S;

    BaseStage(Successor successor) : _successor{successor} {}

    Status receive(Input&& value) {
        auto& stage = *(static_cast<Derived*>(this)); // downcasting to the exact type of Stage via CRTP
        return stage.receive_impl(std::forward<Input>(value));
    }

    Successor _successor;
};

}
}
}
