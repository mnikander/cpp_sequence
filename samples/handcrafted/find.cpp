template <typename I, typename P>
I find(I first, I last, P predicate)
{
    for ( ; first != last; ++first)
    if(predicate(first))
    {
        return first;
    }
    return first;
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
