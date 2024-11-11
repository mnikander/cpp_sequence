template <typename F, typename A, typename I, typename P>
A fold_left(F function, A accumulator, I first, I last, P predicate)
{
    while (predicate(accumulator, first, last))
    {
        accumulator = function(accumulator, first, last);
        ++first;
    }
    return accumulator;
}

template <typename A, typename I>
bool inBounds(A accumulator, I first, I last)
{
    (void)accumulator;
    return first != last;
}

template <typename A, typename I>
A plus(A accumulator, I first, I last)
{
    (void)last;
    return accumulator + first;
}

int main()
{
    int result = 0;
    result     = fold_left(plus<int, int>, 0, 0, 5, inBounds<int, int>);
    return result;
}
