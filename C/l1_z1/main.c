#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
    int r,m,d,n,kal[6][7]; // deklaracja danych
    scanf("%4d%2d%2d",&r,&m,&d); // wczytywanie danych

    // ustawienie n na liczbe dni w danym miesiacu
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) n=31;
    else if(m == 2) n=28;
    else n=30;

    if(d > 7 || m > 12) // sprawdzanie poprawnosci danych
    {
        printf("BLAD DANYCH");
        return 0;
    }

    for(int i=0;i<6;i++) // wyzerowanie tablicy kalendarza
    {
        for(int j=0;j<7;j++)
        {
            kal[i][j]=0;
        }

    }

    int l=1; // ustawienie licznika do generowania dni
    for(int j=d-1;j<7;j++) // wygenerowanie pierwszego wiersza
    {
        kal[0][j]=l;
        l++;
    }
    for(int i=1;i<6;i++) // wygenerowanie pozostalych wierszy
    {
        for(int j=0;j<7;j++)
        {
            kal[i][j]=l;
            l++;
            if(l>n) break;
        }
        if(l>n) break;
    }

    for(int i=0;i<6;i++) // wypisanie kalendarza
    {
        for(int j=0;j<7;j++)
        {
            if(kal[i][j]==0) printf("   ");
            else printf("%2d ", kal[i][j]);
        }
        printf("\n");
    }

    return 0;
}
