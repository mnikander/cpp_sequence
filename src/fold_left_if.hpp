#pragma once

namespace fp {

template <typename F, typename P, typename A, typename I, typename S>
A fold_left_if(F function, P predicate, A accumulator, I first, S sentinel)
{
    while ((first != sentinel) && predicate(accumulator, first, sentinel))
    {
        accumulator = function(accumulator, first, sentinel);
        ++first;
    }
    return accumulator;
}

}
