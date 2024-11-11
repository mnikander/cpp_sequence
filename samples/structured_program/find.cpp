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
bool keepSearching(A accumulator, I current, I last)
{
    (void)current;
    (void)last;
    const bool done_searching = (accumulator == 4);
    return !done_searching;
}

template <typename A, typename I>
A current(A accumulator, I current, I last)
{
    (void)last;
    accumulator = current;
    return accumulator;
}

int main()
{
    int result = 0;
    result = fold_left(current<int, int>, 0, 0, 5, keepSearching<int, int>);
    return result;
}
