#include <stdlib.h>
#include <stdio.h>

long long a,b;
int odp=0;

int suma4cyfr(long long x)
{
    int c1=0;
    int c2=0;
    int c3=0;
    int c4=0;
    while(x>0)
    {
        c4=c3;
        c3=c2;
        c2=c1;
        c1=x%10;
        x/=10;
    }
    return c1+c2+c3+c4;
}

int podcyfr(long long x)
{
    int sc = suma4cyfr(x);

    // jesli liczba jest 4+ cyfrowa i nie spelnia warunku to nie spelnia warunku
    if(x>999 && (sc%22) == 0) return 1;
    else if(x>999) return 0;

    // jesli jest 3 cyfrowa to moze spelniac warunek o ile suma 3 cyfr jest modulo 22 wieksza/rowna 13
    if(x>99 && (sc%22) >= 13) return 1;
    else if(x>99) return 0;

    // jesli jest 2 cyfrowa to moze spelniac warunek o ile suma 2 cyfr jest modulo 22 wieksza/rowna 4
    if(x>9 && (sc%22) >= 4) return 1;
    else if(x>9) return 0;

    // jesli jest 1 cyfrowa to dalej moze spelniac warunek
    return 1;
}

int sumapar(long long x)
{
    int par=0;
    int npar=0;
    int ile=0;

    while(x>0)
    {
        if(ile%2 == 0)
        {
            par += (x%10);
        }
        else
        {
            npar += (x%10);
        }
        ile++;
        x/=10;
    }

    if(ile%2 == 0) return par;
    else return npar;
}

int sumanpar(long long x)
{
    int par=0;
    int npar=0;
    int ile=0;

    while(x>0)
    {
        if(ile%2 == 0)
        {
            par += (x%10);
        }
        else
        {
            npar += (x%10);
        }
        ile++;
        x/=10;
    }

    if(ile%2 == 1) return par;
    else return npar;
}

int dlugosc(long long x)
{
    int ile=0;
    while(x>0)
    {
        ile++;
        x/=10;
    }
    return ile;
}

int parnpar(long long x)
{
    int poz = 12 - dlugosc(x);
    // jesli suma cyfr na parzystych pozycjach nawet jesli na wszystkich pozostalych parzystych postawimy 9, oraz na pozostalych nieparzystych 1
    // nie spelnia warunku to nie ma mozliwosc zeby spelniony byl warunek
    if(sumapar(x) + ((poz+1)/2)*9 < sumanpar(x) + 19 + (poz+2)) return 0;
    return 1;
}

int war3(long long x)
{
    int pop=0;
    int poppop=0;

    while(x>0)
    {
        if(x%10 == 3 && poppop == 3 && pop == 3) return 1;
        poppop = pop;
        pop = x%10;
        x/=10;
    }
    return 0;
}

int war7(long long x)
{
    int pop=0;

    while(x>10)
    {
        if(x%10 == 7 && pop == 7) return 1;
        pop = x%10;
        x/=10;
    }
    return 0;
}

int war3i7(long long x)
{
    int poz = 12 - dlugosc(x);
    if(war3(x) == 1)
    {
        if(war7(x) == 1) return 1;
        else if(poz>=2) return 1;
        else return 0;
    }
    else
    {
        if(war7(x) == 1 && poz>=3) return 1;
        else if(poz>=5) return 1;
        else return 0;
    }
    return 0;
}


int spelnia(long long x)
{
    if(suma4cyfr(x)%22 == 0 && sumapar(x) >= sumanpar(x)+19 && war3(x) == 1 && war7(x) == 1 && x<=b && x>=a) return 1;
    //printf("%d %d %d %d %d\n", suma4cyfr(x), sumapar(x), sumanpar(x), war3(x), war7(x));
    return 0;
}

void rek(long long x)
{
    if(podcyfr(x) == 0 || parnpar(x) == 0 || war3i7(x) == 0 || x > b) return;
    //printf("%lld\n", x);
    if(spelnia(x) == 1) 
    {
        printf("SPELNIA %lld\n", x);
        odp++;
    }
    for(int i=0; i<=9; i++)
    {
        rek(x*10 + i);
    }
}

void sprawdz(long long x)
{
    long long h=x;
    if(spelnia(x) == 1)
    {
        while(x>0)
        {
            if(podcyfr(x) == 0 || parnpar(x) == 0 || war3i7(x) == 0 || x > b) 
            {
                printf("BLAD LICZBY: %lld od %lld\n", x, h);
            }
            x/=10;
        }
    }
    else
    {
        //printf("LICZBA: %lld NIE SPELNIA ", x);
        //if(podcyfr(x) == 1 && parnpar(x) == 1 && war3i7(x) == 1) printf(",ALE MOZE SPELNIAC\n");
        //else printf("\n");
    }
    return;
}


int main()
{
    a=1;
    b=9999999999999;
    for(int i=a; i<=b; i++)
    {
        sprawdz(i);
    }

    return 0;
}