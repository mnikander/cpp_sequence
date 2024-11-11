#include <utility>
#include <vector>

template <typename F, typename A, typename I, typename P>
A fold_left(F function, A accumulator, I current, I sentinel, P predicate)
{
    while (predicate(accumulator, current, sentinel))
    {
        accumulator = function(accumulator, current, sentinel);
        ++current;
    }
    return accumulator;
}


template <typename A, typename I>
bool inBounds(A const& accumulator, I current, I sentinel)
{
    (void)accumulator;
    return current != sentinel;
}

struct Vectors
{
    std::vector<size_t> _a{0u, 2u, 4u, 6u, 8u};
    std::vector<size_t> _b{1u, 3u, 5u, 7u, 9u};
    std::vector<std::pair<size_t, size_t>> _result{};
};

template <typename I>
Vectors& zip(Vectors& vectors, I current, I sentinel)
{
    (void)sentinel;
    vectors._result.push_back(std::make_pair(vectors._a[current], vectors._b[current]));
    return vectors; 
}

int main()
{
    Vectors result{};
    result = fold_left(zip<size_t>, result, 0u, 5u, inBounds<Vectors, size_t>);
    return static_cast<int>(result._result[4u].first + result._result[4u].second);
}
