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
std::vector<A>& append_if_divisible_by_two(std::vector<A>& output, I first, I last)
{
    if(first % 2 == 0) // TODO: make predicate a parameter and find a way to pass it into reduce
    {
        output.push_back(first);
    }
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
    result = reduce(append_if_divisible_by_two<int, int>, result, 0, 5, inBounds<int, int>);
    return result[2];
}
