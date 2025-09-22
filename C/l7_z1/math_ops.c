#include <limits.h>
#include "math_ops.h"

int factorial(int n)
{
    if(n < 0) return 0;
    int w = 1;

    for(int i=1; i<=n; i++)
    {
        if(w >= INT_MAX/i) return -1;
        w*=i;
    }

    return w;
}

double power(double base, int exponent)
{
    double w = 1;

    while(exponent > 0)
    {
        if(exponent%2 == 1) w *= base;
        base *= base;
        exponent /= 2;
    }

    return w;
}

int is_prime(int n)
{
    if(n == 0) return 0;
    for(int i=2; i<n; i++)
    {
        if(n%i == 0) return -1;
    }
    return 1;
}