#pragma once

namespace msp {

// I think 'map' is really just: 'compose' inside the context of an iteration

template <typename F, typename G>
struct compose
{
    using ResultType = typename F::ResultType;

    compose(F f, G g)
        : _f{f}, _g{g} {}

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        return _f(i, _g(i, input));
    }

    F _f;
    G _g;
};

template <typename F, typename G>
struct reverse_compose
{
    using ResultType = typename G::ResultType;

    reverse_compose(F f, G g)
        : _f{f}, _g{g} {}

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        return _g(i, _f(i, input));
    }

    F _f;
    G _g;
};

}
