#pragma once
#include <utility> // forward
#include "basic_datatypes.hpp"

namespace seq {

// Since I need to pass 'emit' as a function object which the user can use in his transform function, emit should not
// have its own template parameter value. Instead, we have to set it at construction by getting the type information
// from the successor stage. This means that while values propagate through the pipeline from start to finish, type
// information propagates through the pipeline backwards, from finish to start.
template<typename S>
struct Emit {
    // this constructor must take the successor as a reference, so that it refers to the _same instance_ of the
    // successor, as the pipeline stage which is using this emitter. Otherwise state updates in the successor stage
    // may become incosistent, since there are multiple copies of each stage.
    Emit(S& successor) : _successor{successor} {}

    void operator()(typename S::value_type&& value) {
        _successor.receive(std::forward<typename S::value_type>(value));
    }

    S& _successor;
};

}
