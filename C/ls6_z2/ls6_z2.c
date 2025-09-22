#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main()
{
    int n, a, r[1001];
    srand(time(NULL));
    for(int i=1; i<=1000; i++) r[i] = rand();

    scanf("%d", &n);

    int p[n+2], s[n+2];

    p[0] = 0;
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a);
        p[i] = (p[i-1]^r[a]);
    }

    s[0] = 0;
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a);
        s[i] = (s[i-1]^r[a]);
    }

    int q, x, y, k;

    scanf("%d", &q);
    for(int i=1; i<=q; i++)
    {
        scanf("%d%d%d", &x, &y, &k);
        x++;
        y++;
        if((p[x+k]^p[x-1]) == (s[y+k]^s[y-1])) printf("TAK\n");
        else printf("NIE\n");
    }

    return 0;
}