#pragma once

namespace fp {

template <typename F, typename P, typename A, typename I>
A fold_left(F function, P stopping_predicate, A accumulator, I current, I sentinel)
{
    while (current != sentinel)
    {
        accumulator     = function(accumulator, current, sentinel);
        if(stopping_predicate(accumulator, current, sentinel))
        {
            return accumulator;
        }
        ++current;
    }
    return accumulator;
}

}
