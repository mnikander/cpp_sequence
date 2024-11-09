#include <vector>

template <typename F, typename A, typename I, typename P>
A reduce(F function, A accumulator, I first, I last, P predicate)
{
    while (predicate(accumulator, first, last))
    {
        accumulator = function(accumulator, first, last);
        ++first;
    }
    return accumulator;
}


template <typename A, typename I>
bool inBounds(A const& accumulator, I first, I last)
{
    (void)accumulator;
    return first != last;
}

struct Vectors
{
    std::vector<int> _a{0, 2, 4, 6, 8};
    std::vector<int> _b{1, 3, 5, 7, 9};
    std::vector<int> _result{};
};

template <typename I>
Vectors& zip(Vectors& vectors, I first, I last)
{
    vectors._result.push_back(vectors._a[first] + vectors._b[first]);
    return vectors; 
}

int main()
{
    Vectors result{};
    result = reduce(zip<int>, result, 0, 5, inBounds<Vectors, int>);
    return result._result[4];
}
