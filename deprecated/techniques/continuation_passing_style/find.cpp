template <typename P, typename I, typename C>
void find(P predicate, I current, I sentinel, C continuation)
{
    if(current == sentinel || predicate(current))
    {
        continuation(current);
    }
    else
    {
        find(predicate, ++current, sentinel, continuation);
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
    find(isFour, 0, 5, assign{result});
    return result;
}
