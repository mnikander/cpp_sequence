#pragma once

#include <string>

namespace smp {

template <typename T>
struct for_loop_object
{
    for_loop_object(int first, int last, T result) : _i{first}, _last{last}, _result{result} {}

    int operator++() { return ++_i; }
    bool keep_going() const { return _i != _last; }

    int _i;
    int const _last;
    T _result;
};


template <typename LoopCondition, typename Block>
constexpr auto iterate(LoopCondition loop, Block block)
{
    while (loop.keep_going())
    {
        loop._result = block(loop._i, loop._result);
        ++loop;
    }
    return loop._result;
}

}
