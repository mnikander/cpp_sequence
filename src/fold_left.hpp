#pragma once

namespace fp {

template <typename F, typename P, typename A, typename I, typename S>
A fold_left(F function, P stopping_predicate, A accumulator, I current, S sentinel)
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
