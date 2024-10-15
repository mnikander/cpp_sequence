#pragma once

namespace msp {

template <typename BlockFirst, typename BlockSecond>
constexpr auto sequence(BlockFirst block_first, BlockSecond block_second)
{
    // I will have to unpack this pair and do something with the two results at
    // the call-site of sequence :S
    return std::make_pair(block_first(), block_second());
}

}
