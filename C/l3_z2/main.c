#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKS_DLUGOSC_TEKSTU 1000


int main(int argc, char *argv[])
{
    int zloty[3] = {1,2,5};
    int groszy[6] = {1,2,5,10,20,50};

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


    // JESLI LICZBA NIE MO¯E ZACZYNAÆ SIÊ LUB KOÑCZYÆ KROPK¥/PRZECINKIEM:
    /*if(tekst[0] == ',' || tekst[0] == '.' || tekst[n-1] == ',' || tekst[n-1] == '.')
    {
            printf("BBLAD");
            return 3;
    }*/

    // WYCIAGANIE CZESCI CALKOWITEJ
    int wskaznik=0;
    int cCalkowita=0;
    while(wskaznik<n && tekst[wskaznik]!='.' && tekst[wskaznik]!=',')
    {
        if('0' <= tekst[wskaznik] && tekst[wskaznik] <= '9')
        {
            cCalkowita = cCalkowita*10 + (tekst[wskaznik] - '0');
        }
        else
        {
            printf("BLAD");
            return 3;
        }
        wskaznik++;
    }
    wskaznik++;


    // WYCIAGANIE CZESCI ULAMKOWEJ
    int cUlamkowa=0;
    while(wskaznik<n)
    {
        if('0' <= tekst[wskaznik] && tekst[wskaznik] <= '9')
        {
            cUlamkowa = cUlamkowa*10 + (tekst[wskaznik] - '0');
        }
        else
        {
            printf("BLAD");
            return 3;
        }
        wskaznik++;
    }


    // SPRAWDZENIE CZY CZESC ULAMKOWA JEST POPRAWNA
    if(cUlamkowa > 99)
    {
        printf("BLAD");
        return 3;
    }


    // OBLICZANIE ZLOTOWEK
    for(int i=2; i>=0; i--)
    {
        if(cCalkowita>=zloty[i])
        {
            printf("%dx%dzl\n",cCalkowita/zloty[i],zloty[i]);
            cCalkowita %= zloty[i];
        }
    }


    // OBLICZANIE GROSZOWEK
    for(int i=5; i>=0; i--)
    {
        if(cUlamkowa>=groszy[i])
        {
            printf("%dx%dgr\n",cUlamkowa/groszy[i],groszy[i]);
            cUlamkowa %= groszy[i];
        }
    }


    return 0;
}
