#pragma once

#include <string>

#include "../compose.hpp"
#include "../example_predicates.hpp"
#include "../iterate.hpp"
#include "get.hpp"

namespace msp {

// should 'from' be a generator, or should it just be a getter, which lives inside the loop defined by a generator?

template <typename Container, typename Block>
struct from
{
    using ResultType = typename Block::ResultType;
    explicit from(Container const& c, Block block) : _container{c}, _block{block} {}

    template <typename Arg>
    ResultType operator()(int i, Arg const& argument) const
    {
        // TODO: I could try to make `f` a member instead of the container and the block
        auto condition = sample::less_than{static_cast<int>(_container.size())};
        auto getter    = get{_container};
        auto f         = iterate{condition, compose{_block, getter}}; // we call: block(getter)
        return f(i, argument);
    }

    // TODO: this feels REALLY unsafe, and holding references as members is strongly discouraged by the cpp core
    // guidelines. Should I hold a raw pointer instead? Would that really make it safer in practice?
    Container const& _container;
    Block _block;
};

}
