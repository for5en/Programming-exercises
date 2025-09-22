#include <stdlib.h>
#include <stdio.h>


int gcd_imp(int p, int q)
{
    int h;
    if(p > q)
    {
        h = p;
        p = q;
        q = h;
    }

    while(p != 0)
    {
        q = q % p;
        
        // swap
        h = p;
        p = q;
        q = h;
    }
    
    return q;
}

int gcd_fun(int p, int q)
{
    if(p == 0) return q;
    
    if(p < q) return gcd_fun(q%p, p);
    else return gcd_fun(p%q, q);
}

void co_prime_imp(int n)
{
    for(int i=1; i<n; i++)
    {
        if(gcd_imp(n,i) == 1) printf("%d ", i);
    }
}

void co_prime_fun(int k, int n)
{
    if(k >= n) return;
    if(gcd_fun(k, n) == 1) printf("%d ", k);
    co_prime_fun(k+1, n);
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);

    printf("IMPERATYWNIE\n%d\n\n", gcd_imp(a, b));
    printf("FUNKCYJNIE\n%d\n\n\n", gcd_fun(a,b));


    int n;
    scanf("%d", &n);

    printf("IMPERATYWNIE\n");
    co_prime_imp(n);
    printf("\nFUNKCYJNIE\n");
    co_prime_fun(1,n);


    return 0;
}