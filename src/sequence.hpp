#pragma once

namespace msp {

template <typename BlockFirst, typename BlockSecond>
constexpr auto sequence(BlockFirst block_first, BlockSecond block_second)
{
    return block_second(block_first());
}

}
