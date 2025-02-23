// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "../src/datatypes.hpp"
#include "crtp_base_stage.hpp"

namespace seq {
namespace proto {
namespace crtp {

template <typename I, typename S>
struct TakeImpl : BaseStage<I, S, TakeImpl<I, S>> {
    using Input     = I;
    using Successor = S;

    TakeImpl(i64 howMany, S successor) : BaseStage<I, S, TakeImpl<I, S>>(successor), _howMany{howMany} { assert(_howMany >= 0); }

    Status receive_impl(Input&& value) {
        if (_counter < _howMany) {
            _counter++;
            return this->_successor.receive(std::forward<typename S::Input>(value));
        }
        else {
            return HALT;
        }
    }

    i64 const _howMany;
    i64 _counter{0};
};

template <typename I, typename S>
auto take(i64 howMany, S successor) {
    return TakeImpl<I, S>{howMany, successor};
}

}
}
}
