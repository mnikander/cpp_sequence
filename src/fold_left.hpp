#pragma once

namespace fp {

template <typename F, typename P, typename A, typename I>
A fold_left(F function, P predicate, A accumulator, I current, I sentinel)
{
    while (current != sentinel && predicate(accumulator, current, sentinel))
    {
        accumulator = function(accumulator, current, sentinel);
        ++current;
    }
    return accumulator;
}

}
