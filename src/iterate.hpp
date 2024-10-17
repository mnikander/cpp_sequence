#pragma once

#include <string>

namespace msp {

// TODO: I might be able to get rid of the 'ResultType' alias, and derive the return type automatically
//       in any child nodes

template <typename Condition, typename Block>
struct iterate
{
    using ResultType = typename Block::ResultType;

    iterate(Condition condition, Block block)
        : _condition{condition}, _block{block} {}

    template <typename InputType>
    ResultType operator()(int initial, InputType input) const
    {
        int i = initial;
        InputType result = input;

        while (_condition(i, input))
        {
            result = _block(i, result);
            ++i;
        }
        return result;
    }

    Condition _condition;
    Block _block;
};

}
