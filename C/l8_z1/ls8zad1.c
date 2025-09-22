#include <stdio.h>
#include <stdlib.h>
#include "beneficjent.h"

int main()
{
    struct Osoba* os1 = nowa_osoba("Adam", 16);
    struct Osoba* os2 = nowa_osoba("Tomek", 3);
    
    zmien_imie(os1, "Marcin");
    zmien_wiek(os1, 14);

    dodaj_szelmostwo(os1);
    dodaj_szelmostwo(os2);
    dodaj_zasluge(os1);
    dodaj_zasluge(os2);

    wypisz_info(os1);
    wypisz_info(os2);
    if(czy_dostanie_prezent(os1) == 1) printf("dostanie :)\n");
    else printf("dostanie ale rozge >:(\n");
    if(czy_dostanie_prezent(os2) == 1) printf("dostanie :)\n");
    else printf("dostanie ale rozge >:(\n");

    ustaw_statystyki(os1,10,3);

    wypisz_info(os1);
    if(czy_dostanie_prezent(os1) == 1) printf("dostanie :)\n");
    else printf("dostanie ale rozge >:(\n");

    printf("%d\n", komparator(os1,os2));

    usun_osobe(os1);
    wypisz_info(os1);


    
}