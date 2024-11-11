template <typename F, typename A, typename I, typename P>
A fold_left(F function, A accumulator, I current, I sentinel, P predicate)
{
    while (predicate(accumulator, current, sentinel))
    {
        accumulator = function(accumulator, current, sentinel);
        ++current;
    }
    return accumulator;
}

template <typename A, typename I>
bool inBounds(A accumulator, I current, I sentinel)
{
    (void)accumulator;
    return current != sentinel;
}

template <typename A, typename I>
A plus(A accumulator, I current, I sentinel)
{
    (void)sentinel;
    return accumulator + current;
}

int main()
{
    int result = 0;
    result     = fold_left(plus<int, int>, 0, 0, 5, inBounds<int, int>);
    return result;
}
