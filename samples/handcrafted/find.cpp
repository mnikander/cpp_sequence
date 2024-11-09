bool isFour(int i)
{
    return i == 4;
}

int main()
{
    int i = 0;
    for (; i < 5; ++i)
    {
        if(isFour(i))
        {
            return i;
        }
    }

    return i;
}
