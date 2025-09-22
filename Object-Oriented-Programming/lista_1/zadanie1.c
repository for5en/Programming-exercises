#include <stdlib.h>
#include <stdio.h>

int fact_imp(int x)
{
    if(x == 0) return 1;
    for(int i=x-1; i>=2; i--) x*=i;
    
    return x;
}

int binom_imp(int x, int y)
{
    //printf("%d %d %d", fact_imp(x), fact_imp(y), fact_imp(x-y));
    return fact_imp(x)/(fact_imp(y)*fact_imp(x-y));
}

int fact_fun(int x)
{
    if(x == 0) return 1;
    return x*fact_fun(x-1); 
}

int binom_fun(int x, int y)
{
    return fact_fun(x)/(fact_fun(y)*fact_fun(x-y));
}

int main()
{
    int n;

    scanf("%d", &n);

    printf("IMPERATYWNIE\n");
    for(int i=0; i<=n; i++)
    {
        printf("%d ", binom_imp(n,i));
    }

    printf("\nFUNKCYJNIE\n");
    for(int i=0; i<=n; i++)
    {
        printf("%d ", binom_fun(n,i));
    }

    return 0;
}