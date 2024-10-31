#pragma once

#include "../common.hpp"

namespace msp {

// 'from' is a generator, but 'to' is really just an element-wise sink for the results, a 'setter' method basically,
// which lives inside the loop created by the generator. Thus 'from' and 'to' are actually completely different in
// their functionality, unless the generator is treated distinctly, and 'from' and 'to' are just the getter and the
// setter respectively

// TODO
// I could also implement 'tee' which dumps the contents into a range AND calls the next block, so that intermediate 
// results in a chain can be stored in a container or written to std::out.

template <typename Container>
struct to
{
    using ResultType = Nothing; // this is a leaf-node in the computation graph, with no return value

    explicit to(Container & c) : _container{c} {}

    template <typename T>
    ResultType operator()(int i, T const& argument)
    {
       _container[i] = argument;
       return Nothing{};
    }

    // TODO: holding by ref is really unsafe, would a raw pointer be any safer?
    Container & _container;
};

}
