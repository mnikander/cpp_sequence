template <typename F, typename A, typename I, typename C>
void reduce(F function, A accumulator, I first, I last, C continuation)
{
    if (first != last)
    {
        accumulator = function(accumulator, first);
        reduce(function, accumulator, ++first, last, continuation);
    }
    else
    {
        continuation(accumulator);
    }
}

template <typename A, typename T>
A plus(A accumulator, T value)
{
    return accumulator + value;
}

template <typename T>
struct assign
{
    explicit assign(T& t) : _t{t} {}
    void operator()(T const& value)
    {
        _t = value;
    }

    T& _t;
};

int main()
{
    int result = 0;
    reduce(plus<int, int>, 0, 0, 5, assign{result});
    return result;
}
