#include <vector>

template <typename F, typename P, typename A, typename I>
A fold_left(F function, P predicate, A accumulator, I current, I sentinel)
{
    while (predicate(accumulator, current, sentinel))
    {
        accumulator = function(accumulator, current, sentinel);
        ++current;
    }
    return accumulator;
}

template <typename A, typename I>
std::vector<A>& append_if_divisible_by_two(std::vector<A>& output, I current, I sentinel)
{
    (void)sentinel;
    
    if(current % 2 == 0) // TODO: make predicate a parameter and find a way to pass it into fold_left
    {
        output.push_back(current);
    }
    return output; 
}

template <typename A, typename I>
bool inBounds(std::vector<A> const& accumulator, I current, I sentinel)
{
    (void)accumulator;
    return current != sentinel;
}

int main()
{
    std::vector<int> result{};
    result = fold_left(append_if_divisible_by_two<int, int>, inBounds<int, int>, result, 0, 5);
    return result[2];
}
