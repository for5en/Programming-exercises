#include <stdio.h>
#include <stdlib.h>

#include "math_ops.h"
#include "number_utils.h"


int main()
{
    int n;
    printf("Podaj n: ");
    scanf("%d", &n);

    printf("silnia: %d\nliczba cyfr: %d\nsuma cyfr: %d\npierwszosc: %d\n\n", factorial(n), count_digits(n), sum_digits(n), is_prime(n));



    double x;
    int y;

    printf("Podaj x oraz y: ");
    scanf("%lf%d", &x, &y);
    printf("Podane x, do potegi y wynosi: %f\n", power(x,y));



    return 0;
}
