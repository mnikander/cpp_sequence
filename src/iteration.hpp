#pragma once

namespace smp {

struct Something{};


template <typename LoopCondition, typename Block>
constexpr auto iterate(LoopCondition loop_condition, Block block)
{
    while (loop_condition)
    {
        block();
    }
    return Something{};
}

}
