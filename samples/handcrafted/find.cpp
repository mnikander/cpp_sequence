template <typename P, typename I>
I find(P predicate, I current, I sentinel)
{
    for ( ; current != sentinel; ++current)
    if(predicate(current))
    {
        return current;
    }
    return current;
}

bool isFour(int i)
{
    return i == 4;
}

int main()
{
    int i = 0;
    i = find(isFour, 0, 5);
    return i;
}
