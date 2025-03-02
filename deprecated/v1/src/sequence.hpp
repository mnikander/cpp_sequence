#pragma once

namespace msp {

template <typename Glue, typename BlockFirst, typename BlockSecond>
struct sequence
{
    using ResultType = decltype(Glue{}(typename BlockFirst::ResultType{}, typename BlockSecond::ResultType{}));

    sequence(Glue glue, BlockFirst block_first, BlockSecond block_second)
        : _glue{glue}, _block_first{block_first}, _block_second{block_second} {}

    template <typename Arg>
    ResultType operator()(int i, Arg argument)
    {
        return _glue(_block_first(i, argument), _block_second(i, argument));
    }

    Glue _glue;
    BlockFirst _block_first;
    BlockSecond _block_second;
};

}
