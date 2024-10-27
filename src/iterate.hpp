#pragma once

#include <string>

namespace msp {

// TODO: I might be able to get rid of the 'ResultType' alias, and derive the return type automatically
//       in any child nodes

template <typename Predicate, typename Block>
struct iterate
{
    using ResultType = typename Block::ResultType;

    iterate(Predicate predicate, Block block)
        : _predicate{predicate}, _block{block} {}

    template <typename InputType>
    ResultType operator()(int initial, InputType input) const
    {
        int i = initial;
        ResultType result;

        while (_predicate(i, input))
        {
            result = _block(i, result);
            ++i;
        }
        return result;
    }

    Predicate _predicate;
    Block _block;
};

}
