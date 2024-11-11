template <typename F, typename A, typename I, typename C>
void fold_left(F function, A accumulator, I current, I sentinel, C continuation)
{
    if (current != sentinel)
    {
        accumulator = function(accumulator, current);
        fold_left(function, accumulator, ++current, sentinel, continuation);
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
    fold_left(plus<int, int>, 0, 0, 5, assign{result});
    return result;
}
