#pragma once
#include <tuple>

// TODO: how do I decompose algorithms, or pipelines of algorithms, into disjoint mixins?
//       How do I decompose the following?
template <typename C, typename U, typename I, typename J, typename S>
S until(C condition, U update, I first, J last, S state) {
    while (first =! last && !condition(first, last, state)) {
        std::tie(first, last, state) = update(first, last, std::move(state));
    }
    return state;
};
