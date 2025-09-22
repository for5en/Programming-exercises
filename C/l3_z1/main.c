#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKS_DLUGOSC_TEKSTU 1000

int main(int argc, char *argv[])
{
    // WCZYTUJEMY DANE
    if(argc != 2)
    {
        printf("BLAD ARGUMENTOW");
        return 1;
    }
    int n = strlen(argv[1]);
    char tekst[MAKS_DLUGOSC_TEKSTU];


    // KOPIUJEMY TEKST Z ARGUMENTU TO TABLICY TEKST
    if(n > MAKS_DLUGOSC_TEKSTU)
    {
        printf("ZA DLUGI TEKST");
        return 2;
    }
    for(int i=0; i<n; i++) tekst[i] = argv[1][i];


    // ZMIENIAMY TEKST NA PISANY Z MA£EJ LITERY
    for(int i=0; i<n; i++)
    {
        if('A' <= tekst[i] && tekst[i] <= 'Z') tekst[i] = tekst[i] - 'A' + 'a';
    }


    // PÊTLA KTÓRA WYPISUJE TEKST, Z PO KOLEI DU¯YM ZNAKIEM
    for(int i=0; i<n ;i++) // i - duzy znak
    {
        if('a' <= tekst[i] && tekst[i] <= 'z') // POMIJAMY ZNAKI SPOZA ALFABETU (malych liter)
        {
            // wypisujemy pierwsza czesc tekstu
            for(int j=0; j<i; j++)
            {
                printf("%c", tekst[j]);
            }

            // wypisujemy i-ta duza litere
            printf("%c", tekst[i] - 'a' + 'A');

            // wypisujemy druga czesc tekstu
            for(int j=i+1; j<n; j++)
            {
                printf("%c", tekst[j]);
            }

            printf("\n");
        }
    }

    return 0;
}
