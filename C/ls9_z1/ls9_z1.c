#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sortlib.h"

struct pom
{
    char* napis;
    int end;
};

struct pom* readline()
{
    int znak;
    int dl = 1;
    int dla = 0;
    int czy = 0;

    char* napis = (char*)malloc(sizeof(char)*1);
    if(napis == NULL) return NULL;

    znak = getc(stdin);
    while(znak != '\n' && znak != EOF)
    {
        if(isgraph(znak))
        {
            napis[dla] = znak;

            dla++;
            if(dla+1 >= dl)
            {
                dl *= 2;
                napis = (char*)realloc(napis, sizeof(char)*dl);
                if(napis == NULL) return NULL;
            }
            czy = 1;
        }
        else if(czy == 1)
        {
            napis[dla] = ' ';

            dla++;
            if(dla+1 >= dl)
            {
                dl *= 2;
                napis = (char*)realloc(napis, sizeof(char)*dl);
                if(napis == NULL) return NULL;
            }
            
            czy = 0;
        }

        znak = getc(stdin);
    }

    napis[dla] = '\0';

    struct pom* h = (struct pom*)malloc(sizeof(struct pom));
    h->napis = napis;
    if(znak == EOF) 
    {
        //printf("\n");
        h->end = 1;
    }
    else h->end = 0;

    return h;
}


char** cut(char* napis)
{
    if(napis == NULL) return NULL;

    int dltab = 1;
    int dlatab = 0;

    char** tablica = (char**)malloc(sizeof(char*)*dltab);
    if(tablica == NULL) return NULL;
    
    int i = 0;
    int dl;
    int dla;

    while(napis[i] != '\0' && napis[i] != '\n')
    {
        if(dlatab+1 >= dltab)
        {
            dltab *= 2;
            tablica = (char**)realloc(tablica, sizeof(char*)*dltab);
        }

        dla = 0;
        dl = 1;

        tablica[dlatab] = (char*)malloc(sizeof(char)*dl);

        while(napis[i] != ' ' && napis[i] != '\n' && napis[i] != '\0')
        {
            if(dla+1 >= dl)
            {
                dl *= 2;
                tablica[dlatab] = (char*)realloc(tablica[dlatab], sizeof(char)*dl);
            }
            tablica[dlatab][dla] = napis[i];
            dla++;
            i++;
        }
        tablica[dlatab][dla] = '\0';
        if(napis[i] != '\n' && napis[i] != '\0') i++;
        dlatab++;
    }

    if(napis[i] == '\n') tablica[0][strlen(tablica[0])] = '\n';
    tablica[dlatab] = NULL;

    return tablica;
}

void wypisz(char*** tablica)
{
    int wyraz;
    int wiersz = 0;

    while(tablica[wiersz] != NULL)
    {
        wyraz = 0;
        while(tablica[wiersz][wyraz] != NULL)
        {
            fputs(tablica[wiersz][wyraz], stdout);
            putc(' ', stdout);
            wyraz++;
        }
        wiersz++;
        putc('\n', stdout);
    }
}

int kompslow(char* a, char* b) // a(1), b(-1), =(0)   -   ktore mniejsze leksykograficznie
{
    int dla = strlen(a);
    int dlb = strlen(b);
    int i = 0;

    //printf("stringi %s %s\n", a, b);

    while(i<dla && i<dlb)
    {
        if(a[i] < b[i]) 
        {
            //printf("%c < %c\n", a[i], b[i]);
            return 1;
        }
        else if(a[i] > b[i]) 
        {
            //printf("%c < %c\n", b[i], a[i]);
            return -1;
        }

        i++;
    }
    if(dla<dlb) return 1;
    else if(dla>dlb) return -1;

    return 0;
}

int komparator(char*** aptr, char*** bptr) // a(1), b(-1), =(0)   -   ktory mniejszy w porzadku odwrotnym
{
    char ** a = *aptr;
    char ** b = *bptr;

    int ida = 0;
    int idb = 0;
    int h;

    //printf("to %s %s\n", a[0], b[0]);
    while(a[ida] != NULL && b[idb] != NULL)
    {
        h = kompslow(a[ida], b[idb]);
        if(h == 1) return 1;
        else if(h == -1) return -1;
        ida++;
        idb++;
    }
    if(a[ida] == NULL && b[idb] == NULL) return 0;
    else if(a[ida] == NULL) return 1;
    else return -1;
}

int main()
{
    struct pom* wiersz = readline();

    int id = 0;
    int dl = 1;
    char*** tablica = (char***)malloc(sizeof(char**)*dl);

    tablica[id] = cut(wiersz->napis);
    
    while(wiersz->end == 0)
    {
        id++;
        if(id+1 >= dl)
        {
            dl *= 2;
            tablica = (char***)realloc(tablica, sizeof(char**)*dl);
        }
        free(wiersz);
        wiersz = readline();

        tablica[id] = cut(wiersz->napis);
    }
    tablica[id+1] = NULL;

    //wypisz(tablica);

    sortowanie(tablica, (__compar_fn_t)komparator);
    
    wypisz(tablica);

    //fputs(tablica[0][0], stdout);
}