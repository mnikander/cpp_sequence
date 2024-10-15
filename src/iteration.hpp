#pragma once

#include <string>

namespace smp {

struct example_loop_object
{
    example_loop_object(int first, int last) : _i{first}, _last{last} {}

    int operator++() { return ++_i; }
    bool keep_going() const { return _i != _last; }

    int _i;
    int const _last;
    std::string _result{""};
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
