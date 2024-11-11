template <typename I, typename P>
I find(I current, I sentinel, P predicate)
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
    i = find(0, 5, isFour);
    return i;
}
