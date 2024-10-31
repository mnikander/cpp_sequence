#pragma once

#include <type_traits> // is_same

namespace msp {

template <typename Predicate, typename BlockTrue, typename BlockFalse>
struct select
{
    static_assert(std::is_same<typename BlockTrue::ResultType, typename BlockFalse::ResultType>(),
                  "BlockTrue and BlockFalse must have the same ResultType");
    using ResultType = typename BlockTrue::ResultType;

    select(Predicate predicate, BlockTrue block_true, BlockFalse block_false)
        : _predicate{predicate}, _block_true{block_true}, _block_false{block_false} {}

    template <typename Arg>
    ResultType operator()(int i, Arg argument)
    {
        return _predicate(i, argument) ? _block_true(i, argument) : _block_false(i, argument);
    }

    Predicate _predicate;
    BlockTrue _block_true;
    BlockFalse _block_false;
};

}
