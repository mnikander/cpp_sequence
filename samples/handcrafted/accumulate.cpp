template <typename A, typename I>
A plus_reduce(A accumulator, I first, I last)
{
    for (; first != last; ++first)
    {
        accumulator += first;
    }
    return accumulator;
}

int main()
{
    int result = 0;
    result     = plus_reduce(result, 0, 5);
    return result;
}
