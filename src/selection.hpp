#pragma once

namespace msp {

template <typename Condition, typename BlockTrue, typename BlockFalse>
constexpr auto select(Condition condition, BlockTrue block_true, BlockFalse block_false)
{
    if(condition)
    {
        return block_true();
    }
    else
    {
        return block_false();
    }
}

}
