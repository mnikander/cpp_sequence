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
std::vector<A>& append(std::vector<A>& output, I first, I last)
{
    (void)last;
    output.push_back(first);
    return output; 
}

template <typename A, typename I>
bool inBounds(std::vector<A> const& accumulator, I first, I last)
{
    (void)accumulator;
    return first != last;
}

int main()
{
    std::vector<int> result{};
    result = reduce(append<int, int>, result, 0, 5, inBounds<int, int>);
    return result[4];
}
