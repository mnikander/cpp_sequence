#include <vector>

template <typename F, typename A, typename I, typename P>
A fold_left(F function, A accumulator, I current, I last, P predicate)
{
    while (predicate(accumulator, current, last))
    {
        accumulator = function(accumulator, current, last);
        ++current;
    }
    return accumulator;
}

template <typename A, typename I>
std::vector<A>& append_if_divisible_by_two(std::vector<A>& output, I current, I last)
{
    (void)last;
    
    if(current % 2 == 0) // TODO: make predicate a parameter and find a way to pass it into fold_left
    {
        output.push_back(current);
    }
    return output; 
}

template <typename A, typename I>
bool inBounds(std::vector<A> const& accumulator, I current, I last)
{
    (void)accumulator;
    return current != last;
}

int main()
{
    std::vector<int> result{};
    result = fold_left(append_if_divisible_by_two<int, int>, result, 0, 5, inBounds<int, int>);
    return result[2];
}
