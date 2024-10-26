#pragma once

namespace msp {

template <typename BlockFirst, typename BlockSecond>
struct compose
{
    using ResultType = typename BlockSecond::ResultType;

    compose(BlockFirst block_first, BlockSecond block_second)
        : _block_first{block_first}, _block_second{block_second} {}

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        return _block_second(i, _block_first(i, input));
    }

    BlockFirst _block_first;
    BlockSecond _block_second;
};

}
