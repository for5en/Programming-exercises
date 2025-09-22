#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// FUNKCJA REKURENCYJNA
double funkcja(int n, int k, double a[], double f[])
{
    if(n < k) return f[n];

    double odp = 0;
    for(int i=0; i<=k-1; i++)
    {
        odp += a[i]*funkcja(n-i-1,k,a,f);
    }
    return odp;
}


// FUNKCJA KTORA SPRAWDZA CZY DANE SLOWO JEST ZEREM (NP. "0.00")
_Bool czyZero(char liczba[])
{
    int dlugosc = strlen(liczba);
    int ileKropek = 0;
    for(int i=0; i<dlugosc; i++)
    {
        if(liczba[i] == '.') ileKropek++;
        else if(liczba[i] != '0') return 0;
    }
    if(ileKropek > 1) return 0;
    return 1;
}


int main(int argc, char *argv[])
{
    unsigned int n;
    scanf("%d", &n);

    // SPRAWDZENIE CZY POPRAWNE ARGUMENTY
    if(argc < 3)
    {
        return 1;
    }

    if(argc-2 != 2*atoi(argv[1]))
    {
        return 2;
    }

    // INTERPRETACJA DANYCH
    int k = atoi(argv[1]);
    double a[k];
    double f[k];

    for(int i=1; i<=k; i++)
    {
        a[i-1]=atof(argv[i+1]);
        if(a[i-1] == 0 && !czyZero(argv[i+1]))
        {
            printf("BLAD DANYCH");
            return 3;
        }
    }

    for(int i=1; i<=k; i++)
    {
        f[i-1]=atof(argv[k+i+1]);
        if(f[i-1] == 0 && !czyZero(argv[k+i+1]))
        {
            printf("BLAD DANYCH");
            return 3;
        }
    }

    // ODPOWIEDZ
    printf("%f", funkcja(n,k,a,f));


    return 0;
}
