#pragma once

#include <string>

namespace msp {

template <typename Condition, typename Block>
constexpr auto iterate(Condition condition, Block block)
{
    int i = 0;
    auto result = typename Block::ResultType{};
    
    while (condition(i, result))
    {
        result = block(i, result);
        ++i;
    }
    return result;
}

}
