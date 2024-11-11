template <typename I, typename P, typename C>
void find(I current, I last, P predicate, C continuation)
{
    if(current == last || predicate(current))
    {
        continuation(current);
    }
    else
    {
        find(++current, last, predicate, continuation);
    }
}

bool isFour(int i)
{
    return i == 4;
}

template <typename T>
struct assign
{
    explicit assign(T& t) : _t{t} {}
    void operator()(T & t)
    {
        _t = t;
    }

    T& _t;
};

int main()
{
    int result = 0;
    find(0, 5, isFour, assign{result});
    return result;
}
