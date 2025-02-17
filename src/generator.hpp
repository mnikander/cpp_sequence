#pragma once
#include <utility> // forward
#include "functional/identity.hpp"
#include "basic_datatypes.hpp"
#include "stage.hpp"

namespace seq {

// Is there a better way to make iteration end, than using the limit in the 'yield' function?
// A later stage could communicate when to terminate the iteration, via a return value.
// This would complicate the design though, and make it similar to my prior design.
// Let's try it without back-communication, and see if we get a simpler design, which actually works.

template <typename F, typename S>
struct Generator : public Stage<mut_i64, F, S> {
    using value_type = mut_i64;

    Generator(F transformation, S successor) : Stage<mut_i64, F, S>{transformation, successor} {}

    void yield(mut_i64 const count = 1) {
        for(mut_i64 i = 0; i < count; ++i) {
            Stage<mut_i64, F, S>::receive(std::forward<value_type>(_index));
            ++_index;
        }
    }

    mut_i64 _index{0};
};

template <typename S>
Generator<Identity, S> make_generator(S successor) {
    return Generator<Identity, S>{Identity{}, successor};
}

template <typename F, typename S>
Generator<F, S> make_generator(F function, S successor) {
    return Generator<F, S>{function, successor};
}

}
