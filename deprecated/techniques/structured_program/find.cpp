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
bool keepSearching(A accumulator, I current, I sentinel)
{
    (void)current;
    (void)sentinel;
    const bool done_searching = (accumulator == 4);
    return !done_searching;
}

template <typename A, typename I>
A current(A accumulator, I current, I sentinel)
{
    (void)sentinel;
    accumulator = current;
    return accumulator;
}

int main()
{
    int result = 0;
    result = fold_left(current<int, int>, keepSearching<int, int>, 0, 0, 5);
    return result;
}
