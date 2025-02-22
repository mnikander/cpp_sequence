// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {
namespace dir {

template <typename I, typename S>
struct TakeImpl {
    using Input = I;

    TakeImpl(i64 howMany, S successor) : _howMany{howMany}, _successor{successor} { assert(_howMany >= 0); }

    Status receive(Input&& value) {
        if (_counter < _howMany) {
            _counter++;
            return _successor.receive(std::forward<typename S::Input>(value));
        }
        else {
            return HALT;
        }
    }

    i64 const _howMany;
    i64 _counter{0};
    S _successor;
};

template <typename I, typename S>
auto take(i64 howMany, S successor) {
    return TakeImpl<I, S>{howMany, successor};
}

}
}
