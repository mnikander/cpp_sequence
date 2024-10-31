#pragma once

namespace msp {

template <typename Container>
struct get
{
    using ResultType = typename Container::value_type;

    explicit get(Container const& container) : _container{container} {}

    template <typename Arg>
    ResultType operator()(int i, Arg argument) const
    {
        (void)argument;
        return _container[i];
    }

    Container const& _container;
};

}
