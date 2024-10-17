#pragma once

#include <type_traits> // is_same

namespace msp {

template <typename Condition, typename BlockTrue, typename BlockFalse>
struct select {
    
    static_assert(std::is_same<typename BlockTrue::ResultType, typename BlockFalse::ResultType>(),
                  "BlockTrue and BlockFalse must have the same ResultType");
    using ResultType = typename BlockTrue::ResultType;

    select(Condition condition, BlockTrue block_true, BlockFalse block_false)
        : _condition{condition}, _block_true{block_true}, _block_false{block_false} {}

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        return _condition(i, input) ? _block_true(i, input) : _block_false(i, input);
    }

    Condition _condition;
    BlockTrue _block_true;
    BlockFalse _block_false;
};

}
