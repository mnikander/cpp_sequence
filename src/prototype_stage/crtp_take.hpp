// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "../datatypes.hpp"
#include "crtp_ base_stage.hpp"

namespace seq {

template <typename I, typename S>
struct CrtpTake : BaseStage<I, S, CrtpTake<I, S>> {
    using Input     = I;
    using Successor = S;

    CrtpTake(i64 howMany, S successor) : BaseStage<I, S, CrtpTake<I, S>>(successor), _howMany{howMany} { assert(_howMany >= 0); }

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
auto takeCrtp(i64 howMany, S successor) {
    return CrtpTake<I, S>{howMany, successor};
}

}
