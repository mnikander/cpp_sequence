// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../../datatypes.hpp"

namespace seq {

// To pass a value to the next stage in the pipeline, we need a reference to the next stage, and we need to know the
// Input type it works with. This means that values propagate forwards through the pipeline from the beginning to the
// end, but type information propagates through the pipeline backwards, from the end to the beginning.

template<typename S>
struct Emit {
    // this constructor must take the successor as a reference, so it refers to the _same instance_ of the successor as
    // the pipeline stage which is using this emitter. Otherwise there would be multiple copies of each stage.
    Emit(S& successor) : _successor{successor} {}

    Status operator()(typename S::Input&& value) {
        return _successor.receive(std::forward<typename S::Input>(value));
    }

    S& _successor;
};

}
