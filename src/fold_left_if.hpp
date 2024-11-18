#pragma once

namespace fp {

template <typename F, typename P, typename A, typename I, typename S>
A fold_left_if(F function, P stopping_predicate, A accumulator, I current, S sentinel)
{
    while (current != sentinel && !stopping_predicate(accumulator, current, sentinel))
    {
        accumulator = function(accumulator, current, sentinel);
        ++current;
    }
    return accumulator;
}

}
