#include <stdio.h>
#include <stdlib.h>

int gcd(int x, int y)
{
    int h;
    while(x != 0)
    {
        if(x < y) h=x, x=y, y=h;
        x %= y;
    }
    return y;
}

int nww(int x, int y, int z)
{
    return (x*y/gcd(x,y))*z/gcd((x*y/gcd(x,y)),z);
}

int compare(const void *x, const void *y)
{
    return (*(int*)x - *(int*)y);
}

int war[100005];

_Bool sprawdzenie(int n, int x, int y)
{
    int suma = 0;
    for(int i=1; i<=n; i++) suma += (x/war[i]);

    if(suma >= y) return 1;
    else return 0;
}

int main()
{
    int n,r,c;
    int q;
    scanf("%d", &n);
    int tab[n+5];
    //int war[n+5];

    for(int i=1;i<=n;i++) scanf("%d", &tab[i]);
    tab[0] = tab[n];
    tab[n+1] = tab[1];
    for(int i=1;i<=n;i++) war[i] = nww(tab[i-1], tab[i], tab[i+1]);

    scanf("%d%d%d", &r, &c, &q);

    qsort(war+1, n, sizeof(int), compare);
    //for(int i=1;i<=n;i++) printf("%d ", war[i]);

    unsigned long long sr, p=0, k=10e18;

    unsigned long long odp=0;
    while(p<=k)
    {
        sr = p+(k-p)/2;
        if(sprawdzenie(n, sr, r) == 1) 
        {
            odp = sr;
            k=sr-1;
        }
        else p=sr+1;
        //printf("%d %d\n", p, k);
    }

    printf("%llu ", odp);

    int suma = 0;
    int ile=1;
    suma = c/war[1];
    //printf("%d\n", suma);
    while(suma < q)
    {
        ile++;
        suma += (c/war[ile]);
        //printf("%d\n", war[ile]);
    }

    printf("%d", ile);


    return 0;
}