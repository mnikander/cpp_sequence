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
bool keepSearching(A accumulator, I first, I last)
{
    (void)first;
    (void)last;
    const bool done_searching = (accumulator == 4);
    return !done_searching;
}

template <typename A, typename I>
A current(A accumulator, I first, I last)
{
    (void)last;
    accumulator = first;
    return accumulator;
}

int main()
{
    int result = 0;
    result = reduce(current<int, int>, 0, 0, 5, keepSearching<int, int>);
    return result;
}
