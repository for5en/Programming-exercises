#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "beneficjent.h"

struct Osoba* nowa_osoba(char* imie, uint8_t wiek)
{
    static int n = -1;

    struct Osoba* ptr = (struct Osoba*)malloc(sizeof(struct Osoba));
    if(ptr == NULL) return NULL;

    (ptr->imie) = malloc(strlen(imie)+1);
    strcpy(ptr->imie, imie);
    (ptr->wiek) = wiek;

    n++;
    (ptr->id) = (unsigned int)n;

    return ptr;
}

void usun_osobe(struct Osoba* osoba)
{
    free(osoba);
}

void zmien_imie(struct Osoba* osoba, char* imie)
{
    char* ptr = realloc(osoba->imie, strlen(imie)+1);
    if(ptr == NULL) return;

    osoba->imie = ptr;
    strcpy(osoba->imie, imie);
}

void zmien_wiek(struct Osoba* osoba, uint8_t wiek)
{
    (osoba->wiek) = wiek;
}

void dodaj_zasluge(struct Osoba* osoba)
{
    (osoba->zaslugi)++;
}

void dodaj_szelmostwo(struct Osoba* osoba)
{
    (osoba->szelmostwa)++;
}

void ustaw_statystyki(struct Osoba* osoba, unsigned int zaslugi, unsigned int szelmostwa)
{
    (osoba->zaslugi) = zaslugi;
    (osoba->szelmostwa) = szelmostwa;
}

int czy_dostanie_prezent(struct Osoba* osoba)
{
    if((osoba->zaslugi > (osoba->szelmostwa)) || (osoba->wiek) < 4) return 1;
    else return 0;
}

void wypisz_info(struct Osoba* osoba)
{
    fputs(osoba->imie, stdout);
    printf("wiek: %d\nzaslugi: %d\nszelmostwa: %d\nindeks: %d\n\n", (osoba->wiek), (osoba->zaslugi), (osoba->szelmostwa), (osoba->id));
}

int komparator(struct Osoba** os1ptr, struct Osoba** os2ptr)
{
    struct Osoba* os1 = *os1ptr;
    struct Osoba* os2 = *os2ptr;
    printf("%d %d %d %d\n", os1->id, os2->id, (os1->zaslugi)-(os1->szelmostwa), (os2->zaslugi)-(os2->szelmostwa));

    if(((os1->zaslugi)+(os2->szelmostwa)) > ((os2->zaslugi)+(os1->szelmostwa))) return 1;
    else if((os1->zaslugi)+(os2->szelmostwa) < (os2->zaslugi)+(os1->szelmostwa)) return -1;
    else if((os1->wiek) < (os2->wiek)) return 1;
    else if((os1->wiek) >(os2->wiek)) return -1;
    else return 0;
}

struct Osoba* znajdz(int id, int n, struct Osoba** tablica)
{
    for(int i=0; i<=n; i++)
    {
        if((tablica[i]->id) == (unsigned int) id) return tablica[i];
    }
    return NULL;
}