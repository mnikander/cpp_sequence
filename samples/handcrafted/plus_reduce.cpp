template <typename A, typename I>
A plus_reduce(A accumulator, I current, I last)
{
    for (; current != last; ++current)
    {
        accumulator += current;
    }
    return accumulator;
}

int main()
{
    int result = 0;
    result     = plus_reduce(result, 0, 5);
    return result;
}
