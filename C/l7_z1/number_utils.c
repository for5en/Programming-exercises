#include "number_utils.h"

int count_digits(int number)
{
    int w = 1;
    if(number < 0) number = -number;

    number/=10;
    while(number > 0) number/=10, w++;

    return w;
}

int reverse_number(int number)
{
    int w = 0;
    if(number < 0) number = -number;

    while(number > 0)
    {
        w *= 10;
        w = number % 10;
        number /= 10;
    }

    return w;
}

int sum_digits(int number)
{
    int w = 0;
    if(number < 0) number = -number;

    while(number > 0) w+=(number%10), number/=10;

    return w;
}
