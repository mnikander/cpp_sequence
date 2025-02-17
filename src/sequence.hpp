#pragma once
#include <utility> // forward
#include "../src/global_datatypes.hpp"

// Generate a sequence of values and perform arbitrary transformations on it.
// This workflow is heavily inspired by the streaming library in Kotlin.
// It consists of the following three kinds of stages
// - a generator creates values and passes them onwards
// - a sequence stages receives values, transforms them, and passes them onwards, possibly to other intermediate stages
// - at the end, a final stage receives values and writes them into a container -- or it could do a reduction and return a value...

// Since I need to pass 'emit' as a function object which the user can use in his transform function, emit should not
// have its own template parameter value. Instead, we have to set it at construction by getting the type information
// from the successor stage. This means that while values propagate through the pipeline from start to finish, type
// information propagates through the pipeline backwards, from finish to start.
template<typename S>
struct Emitter {
    // this constructor must take the successor as a reference, so that it refers to the _same instance_ of the
    // successor, as the pipeline stage which is using this emitter. Otherwise state updates in the successor stage
    // may become incosistent, since there are multiple copies of each stage.
    Emitter(S& successor) : _successor{successor} {}

    void operator()(typename S::value_type value) {
        _successor.receive(value);
    }

    S& _successor;
};

template <typename T, typename F, typename S>
struct Stage {
    using value_type = T;

    Stage(F transformation, S successor) : _transformation{transformation}, _successor{successor}, _emit{_successor} {}

    void receive(value_type value) {
        _transformation(_emit, value);
    }

    F _transformation;
    S _successor;
    Emitter<S> _emit;
};

template <typename F, typename S>
struct Generator : public Stage<mut_i64, F, S> {
    using value_type = mut_i64;

    Generator(F transformation, S successor) : Stage<mut_i64, F, S>{transformation, successor} {}

    // is there a better way to make iteration end, for example by letting a later stage communicate that?
    // Or would communication from a later stage make the design as complicated as my prior implementation attempts?
    // Let's try it without back communication and see if we get a simpler design, which actually works.
    void yield(mut_i64 const count = 1) {
        for(mut_i64 i = 0; i < count; ++i) {
            Stage<mut_i64, F, S>::receive(_index);
            ++_index;
        }
    }

    mut_i64 _index{0};
};

template <typename Range>
struct RangeSink {
    using value_type = typename Range::value_type;

    RangeSink(Range& range) : _range{range} {}

    void receive(value_type value) {
        *(_range.begin() + _target_index) = value;
        ++_target_index;
    }

    Range& _range;
    mut_i64 _target_index{0};
};

template <typename T, typename F, typename S>
Stage<T, F, S> make_stage(F function, S successor) {
    return Stage<T, F, S>{function, successor};
}

template <typename F, typename S>
Generator<F, S> make_generator(F function, S successor) {
    return Generator<F, S>{function, successor};
}
