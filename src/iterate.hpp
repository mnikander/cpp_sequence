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

    template <typename Arg>
    ResultType operator()(int initial, Arg argument)
    {
        int i = initial;
        ResultType result;

        while (_predicate(i, argument))
        {
            result = _block(i, argument);
            ++i;
        }
        return result;
    }

    Predicate _predicate;
    Block _block;
};

}
