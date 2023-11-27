int dis_x(int n, int xxx[])
{
    x = xxx[n];
    for (int i = n + 1; i < N; i++)
    {
        if (xxx[i] == xxx[i - 1])
        {
            xxx[i]++;
            dis++;
        }
        else
        {
            dis += xxx[i] - (x + (i - n));
            xxx[i] = x + (i - n);
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (xxx[i] == xxx[i + 1])
        {
            xxx[i]--;
            dis++;
        }
        else
        {
            dis += xxx[i] - (x - (n - i));
            xxx[i] = x - (n - i);
        }
    }
    disx = dis;
    dis = 0;
    return disx;
}