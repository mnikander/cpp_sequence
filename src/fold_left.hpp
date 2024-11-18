#pragma once

namespace fp {

template <typename F, typename P, typename A, typename I, typename S>
A fold_left(F function, P stopping_predicate, A accumulator, I current, S sentinel)
{
    bool stop = false;

    while (current != sentinel && !stop)
    {
        accumulator = function(accumulator, current, sentinel);
        stop        = stopping_predicate(accumulator, current, sentinel); // note the updated accumulator value is used
        ++current;
    }
    return accumulator;
}

}
