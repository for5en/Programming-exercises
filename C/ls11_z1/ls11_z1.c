#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_WIERSZ 1000
#define BLAD(x) do {printf("blad%d", x); return x;} while(0)
// gnu c preprocesoor
// swallowing the semicolon

// 10 - 13
// 11 - 7
// 11.2 - 15

struct node
{
    double glos;
    int sum;
    int id;
};

int mystrlen(char* slowo)
{
    int id = 0;
    while(slowo[id] != 0 && slowo[id] != ';' && slowo[id] != '\n') id++;
    return id;
}

char* mystrcpy(char* slowo)
{
    int dl = mystrlen(slowo);
    char* cel = (char*)malloc(sizeof(char)*(dl+1));
    if(cel == NULL) return NULL;

    for(int i=0; i<dl; i++) cel[i] = slowo[i];
    cel[dl] = '\0';

    return cel;
}

void zeruj(int* tablica, int n)
{
    for(int i=0; i<n; i++) tablica[i] = 0;
}

int przetworz(char* wiersz, int** glosow, int* mandatow, int numOkr, int numKom, int* sum, int* sumaKom)
{
    char* ptr = wiersz;
    ptr = ptr + mystrlen(ptr) + 1;
    if(*(ptr-1) == '\n') return 0;

    mandatow[numOkr] = strtoul(ptr, NULL, 10);

    glosow[numOkr] = (int*)malloc(sizeof(int)*numKom);
    if(glosow[numOkr] == NULL) return 0;

    for(int i=0; i<numKom; i++)
    {
        ptr = ptr + mystrlen(ptr) + 1;
        //printf("%c %d\n", *(ptr-2), i);
        if(*(ptr-1) == '\n' && i != numKom-1) return 0;
        
        if(*ptr != ';')
        {
            //printf("%c, %d\n",*ptr, (int)strtoul(ptr,NULL,10));
            glosow[numOkr][i] = (int)strtoul(ptr, NULL, 10);
            //printf("%d %d:  %d\n", numOkr, i, glosow[numOkr][i]);
            (*sum) += glosow[numOkr][i];
            sumaKom[i] += glosow[numOkr][i];
        }
        else glosow[numOkr][i] = 0;
    }

    ptr = ptr + mystrlen(ptr) + 1;
    if(*(ptr-1) != '\n') return 1;

    return 1;
}

int komp(struct node** aptr, struct node** bptr)
{
    struct node* a = *aptr;
    struct node* b = *bptr;
    if((a->glos) < (b->glos)) return 1;
    else if((a->glos) > (b->glos)) return -1;
    else if((a->sum) > (b->sum)) return 1;
    else return -1;
}

int przelicz(int* wynikKom, int** glosow, int* mandatow, int iluSpelnia, int numOkr, int numKom, int* prog)
{
    struct node** okreg = (struct node**)malloc(iluSpelnia*mandatow[numOkr]*sizeof(struct node*));
    if(okreg == NULL) return 0;

    int id=0;
    double h;
    for(int i=0; i<numKom; i++)
    {
        if(prog[i] == 1)
        {
            for(int j=1; j<=mandatow[numOkr]; j++)
            {
                h=j;
                struct node* ptr = (struct node*)malloc(sizeof(struct node));
                if(ptr == NULL) return 0;
                ptr->glos = (double)(glosow[numOkr][i]/h);
                ptr->id = i;
                ptr->sum = glosow[numOkr][i];
                okreg[id] = ptr;
                id++;
            }
        }
    }

    qsort(okreg, id, sizeof(struct node*), (__compar_fn_t)komp);
    for(int i=0; i<mandatow[numOkr]; i++)
    {
        wynikKom[okreg[i]->id]++;
    }
    return 1;
}

int main(int argc, char* argv[])
{
    char buforWiersza[MAX_WIERSZ];
    fgets(buforWiersza, MAX_WIERSZ, stdin);
    
    int dlugoscWiersza = strlen(buforWiersza);
    char* ptr = buforWiersza;

    // pomijam wyrazy "okreg", "mandaty"
    ptr = ptr + mystrlen(ptr) + 1;
    if(*(ptr-1) == '\n') BLAD(4);
    ptr = ptr + mystrlen(ptr) + 1;
    if(*(ptr-1) == '\n') BLAD(3);

    char** komitety = (char**)malloc(sizeof(char*)*(dlugoscWiersza/2));
    int numKom = 0;
    
    while(*(ptr-1) != '\0')
    {
        komitety[numKom] = mystrcpy(ptr);
        if(komitety[numKom] == NULL) BLAD(1);

        ptr = ptr + mystrlen(ptr) + 1;
        numKom++;
    }
    numKom--;

    komitety = (char**)realloc(komitety, sizeof(char*)*numKom);
    if(komitety == NULL) BLAD(2);

    /////////////////////////////////////////////////////////////////////////////////
    
    int sumaG = 0;
    int numOkr = 0;
    int dynTab = 1;
    int **glosow = (int**)malloc(dynTab * sizeof(int*));
    int *mandatow = (int*)malloc(dynTab * sizeof(int));
    int sumaKom[numKom];
    zeruj(sumaKom, numKom);
    if(glosow == NULL || mandatow == NULL) BLAD(5);

    while(feof(stdin) == 0)
    {
        fgets(buforWiersza, MAX_WIERSZ, stdin);
        if(dynTab < numOkr+1)
        {
            dynTab *= 2;
            glosow = (int**)realloc(glosow, dynTab * sizeof(int*));
            mandatow = (int*)realloc(mandatow, dynTab * sizeof(int));
            if(glosow == NULL || mandatow == NULL) BLAD(6);
        }
        if(przetworz(buforWiersza, glosow, mandatow, numOkr, numKom, &sumaG, sumaKom) == 0) BLAD(7);
        numOkr++;
    }

    glosow = (int**)realloc(glosow, numOkr*sizeof(int*));
    if(glosow == NULL) BLAD(9);
    
    int sumaMandatow=0;
    /*printf("numkom: %d\n", numKom);
    for(int i=0; i<numOkr; i++)
    {
        printf("okreg: %d, mandatow: %d  ", i, mandatow[i]);
        sumaMandatow+=mandatow[i];
        for(int j=0; j<numKom; j++)
        {
            printf("%d ", glosow[i][j]);
        }
        printf("\n");
    }*/

    /////////////////////////////////////////////////////////////////////////////////////////////////

    int prog[numKom];
    int iluSpelnia = 0;
    for(int i=0; i<numKom; i++)
    {
        if(sumaKom[i]*20 >= sumaG)
        {
            prog[i] = 1;
            iluSpelnia++;
        }
        else prog[i] = 0;
    }

    int wynikKom[numKom];
    zeruj(wynikKom, numKom);
    for(int i=0; i<numOkr; i++)
    {
        if(przelicz(wynikKom, glosow, mandatow, iluSpelnia, i, numKom, prog) == 0) BLAD(90+i);
    }

    for(int i=0; i<numKom; i++)
    {
        if (wynikKom[i])
            printf("%d %s\n", wynikKom[i], komitety[i]);
    }

    return 0;
}