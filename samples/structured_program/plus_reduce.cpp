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
bool inBounds(A accumulator, I current, I last)
{
    (void)accumulator;
    return current != last;
}

template <typename A, typename I>
A plus(A accumulator, I current, I last)
{
    (void)last;
    return accumulator + current;
}

int main()
{
    int result = 0;
    result     = fold_left(plus<int, int>, 0, 0, 5, inBounds<int, int>);
    return result;
}
