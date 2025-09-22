#include <stdio.h>
#include <stdlib.h>
#define ull unsigned long long

ull iledziel(ull x)
{
    int odp=0;
    for(ull i=1; i*i<=x; i++)
    {
        if(x % i == 0) odp++;
    }
    return odp*2;
}

int main(int argc, char* argv[])
{
    if(argc != 2) return 2;

    char* endptr;
    unsigned long int n = strtoul(argv[1], &endptr, 10);
    if(*endptr != '\0') return 3;

    ull id=2, liczba=1;
    for(; iledziel(liczba) <= n; id++) 
    {
        liczba+=id;
    }
    printf("Indeks: %llu\nLiczba: %llu\n", id, liczba);
    return 0;
}
