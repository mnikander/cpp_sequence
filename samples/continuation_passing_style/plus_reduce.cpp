template <typename A, typename I, typename C>
void plus_reduce(A accumulator, I first, I last, C continuation)
{
    if (first == last)
    {
        continuation(accumulator);
    }
    else
    {
        accumulator+=first;
        plus_reduce(accumulator, ++first, last, continuation);
    }
}

template <typename T>
struct assign
{
    explicit assign(T& t) : _t{t} {}
    void operator()(T const& t)
    {
        _t = t;
    }

    T& _t;
};

int main()
{
    int result = 0;
    plus_reduce(0, 0, 5, assign{result});
    return result;
}
