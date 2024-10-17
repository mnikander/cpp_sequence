#pragma once

namespace msp {

template <typename Condition, typename BlockTrue, typename BlockFalse>
constexpr auto select(Condition condition, BlockTrue block_true, BlockFalse block_false)
{
    return condition ? block_true() : block_false();
}

}
