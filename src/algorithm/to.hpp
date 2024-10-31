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

    // TODO: This works, but we are claiming the member-function is const
    //       even though we are modifying the contents of the container.
    //       Making operator() non-const, breaks the code completely though.
    //       Is the const-ness a false claim on my side? Is this a bug?
    //       Does this need to be fixed?
    template <typename T>
    ResultType operator()(int i, T const& input) const
    {
       _container[i] = input;
       return Nothing{};
    }

    // TODO: holding by ref is really unsafe, would a raw pointer be any safer?
    Container & _container;
};

}
