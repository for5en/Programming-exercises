#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "beneficjent.h"
#define MAX_IMIE 10000

int main()
{
    int ile, id, pol;
    char imie[MAX_IMIE+1];
    int wiek,zaslugi,szelmostwa;

    struct Osoba** tablica;
    struct Osoba* ptr;
    int n = -1;

    while(1)
    {
        if(scanf("%d", &pol)!=1) break;

        if(pol == 0)
        {
            //printf("");
        }
        else if(pol == 1)
        {
            scanf("%d", &ile);
            tablica = (struct Osoba**)realloc(tablica, (n+ile+2)*sizeof(struct Osoba*));

            if(tablica == NULL) return 1;

            for(int i=n+1; i<=n+ile; i++)
            {
                scanf("%d%d%d", &wiek, &zaslugi, &szelmostwa);
                fgets(imie, MAX_IMIE, stdin);

                ptr = nowa_osoba(imie, wiek);
                if(ptr == NULL) return 1;
                tablica[i] = ptr;
                ustaw_statystyki(tablica[i], zaslugi, szelmostwa);
            }
            n = n+ile;
        }
        else if(pol == 2)
        {
            qsort(tablica, n+1, sizeof(struct Osoba*), (__compar_fn_t)komparator);
        }
        else if(pol == 3)
        {
            for(int i=0; i<=n; i++) wypisz_info(tablica[i]);
        }
        else if(pol == 4)
        {
            scanf("%d%d", &id, &wiek);
            ptr = znajdz(id, n, tablica);
            if(ptr != NULL) zmien_wiek(ptr, wiek);
        }
        else if(pol == 5)
        {
            scanf("%d", &id);
            fgets(imie, MAX_IMIE, stdin);
            ptr = znajdz(id, n, tablica);
            if(ptr != NULL) zmien_imie(ptr, imie);
        }
        else if(pol == 6) // || pol == 7
        {
            scanf("%d", &id);
            ptr = znajdz(id, n, tablica);
            if(ptr != NULL) dodaj_zasluge(ptr); // (*(pol == 6 ? dodaj_zasluge : dodaj_szelmostwo))(ptr)
        }
        else if(pol == 7)
        {
            scanf("%d", &id);
            ptr = znajdz(id, n, tablica);
            if(ptr != NULL) dodaj_szelmostwo(ptr);
        }
        else if(pol == 8)
        {
            scanf("%d%d%d", &id, &zaslugi, &szelmostwa);
            ptr = znajdz(id, n, tablica);
            if(ptr != NULL) ustaw_statystyki(ptr, zaslugi, szelmostwa);
        }
        else if(pol == 9)
        {
            scanf("%d", &id);
            ptr = znajdz(id, n, tablica);
            if(ptr != NULL) wypisz_info(ptr);
        }
    }
}