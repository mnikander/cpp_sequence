template <typename F, typename A, typename I, typename P>
A reduce(F function, A accumulator, I first, I last, P predicate)
{
    while (predicate(accumulator, first, last))
    {
        accumulator = function(accumulator, first, last);
        ++first;
    }
    return accumulator;
}

template <typename T>
struct Result
{
    T _value;
    bool _keep_going = true;
};

template <typename A, typename I>
bool keepSearching(A accumulator, I first, I last)
{
    (void)last;
    const bool already_found = (accumulator._value == 4);
    accumulator._keep_going &= !already_found;
    return (accumulator._keep_going);
}

template <typename A, typename I>
A current(A accumulator, I first, I last)
{
    (void)last;
    accumulator._value = first;
    return accumulator;
}

int main()
{
    using R = Result<int>;

    R result{0};
    result = reduce(current<R, int>, R{0}, 0, 5, keepSearching<R, int>);
    return result._value;
}
