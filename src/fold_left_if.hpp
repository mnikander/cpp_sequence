#pragma once

namespace fp {

template <typename F, typename P, typename A, typename I, typename S>
A fold_left_if(F function, P stopping_predicate, A accumulator, I current, S sentinel)
{
    bool stop = false;
    while (current != sentinel && !stop)
    {
        // note that the predicate uses the _updated_ accumulator value
        accumulator = function(accumulator, current, sentinel);
        stop        = stopping_predicate(accumulator, current, sentinel);
        ++current;
    }
    return accumulator;
}

}
