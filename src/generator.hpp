#pragma once
#include <utility> // forward
#include "basic_datatypes.hpp"
#include "stage.hpp"

namespace seq {

template <typename F, typename S>
struct Generator : public Stage<mut_i64, F, S> {
    using value_type = mut_i64;

    Generator(F transformation, S successor) : Stage<mut_i64, F, S>{transformation, successor} {}

    // is there a better way to make iteration end, for example by letting a later stage communicate that?
    // Or would communication from a later stage make the design as complicated as my prior implementation attempts?
    // Let's try it without back communication and see if we get a simpler design, which actually works.
    void yield(mut_i64 const count = 1) {
        for(mut_i64 i = 0; i < count; ++i) {
            Stage<mut_i64, F, S>::receive(std::forward<value_type>(_index));
            ++_index;
        }
    }

    mut_i64 _index{0};
};

template <typename F, typename S>
Generator<F, S> make_generator(F function, S successor) {
    return Generator<F, S>{function, successor};
}

}
