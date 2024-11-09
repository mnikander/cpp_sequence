template <typename A, typename I, typename P, typename B>
A iterate(A accumulator, I first, I last, P predicate, B block)
{
    while (predicate(accumulator, first, last))
    {
        accumulator = block(accumulator, first, last);
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
    result     = iterate(0, 0, 5, inBounds<int, int>, plus<int, int>);
    return result;
}
