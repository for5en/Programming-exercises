#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void genPodciagi(char slowo[21], int dlSlowa, char podciag[], int dlPodciagu, int id, int* ktory, char tablica[195][21], int dlugosci[195])
{
    for(int i=0; i < dlPodciagu; i++)
    {
        tablica[*ktory][i] = podciag[i];
        //printf("%c", podciag[i]);
    }
    dlugosci[*ktory] = dlPodciagu;
    (*ktory)++;

    //printf("\n");

    for(int i=id+1; i< dlSlowa;i++)
    {
        podciag[dlPodciagu] = slowo[i];
        genPodciagi(slowo, dlSlowa, podciag, dlPodciagu+1, i, ktory, tablica, dlugosci);
    }
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("ZA MALO ARGUMENTOW");
        return 1;
    }

    int dlugosc = strlen(argv[1]);

    int ktory = 0; // licznik podslow
    int dlugosci[195]; // dlugosci kolejnych podslow
    char tablica[195][21] = {0}; // tablica podslow

    // flagi
    int iFlag = -1;
    _Bool aFlag = 0;

    char cos[21]; // tablica z niczym do inicjalizacji genPodciagi
    genPodciagi(argv[1],dlugosc,cos,0, -1, &ktory, tablica, dlugosci);


    // sprawdzanie flag i ich poprawnosci
    for(int i=2; i<argc; i++)
    {
        if(argv[i][0] == '-' && strlen(argv[i]) == 2)
        {
            if(argv[i][1] == 'a' && aFlag == 0)
            {
                aFlag = 1;
            }
            else if(argv[i][1] == 'i' && iFlag == -1)
            {
                if(i+1 < argc)
                {
                    iFlag = atoi(argv[i+1]);
                    if(iFlag <= 0)
                    {
                        printf("BLAD FLAG");
                        return 2;
                    }
                }
            }
            else
            {
                printf("BLAD FLAG");
                return 2;
            }
        }
    }

    // wypisywanie odpowiedzi w zaleznosci od podanych flag
    if(iFlag != -1)
    {
        if(iFlag + aFlag < ktory)
        {
            for(int j=0; j<dlugosci[iFlag + aFlag]; j++) printf("%c", tablica[iFlag + aFlag][j]);
        }
        else
        {
            printf("BLAD FLAG");
            return 2;
        }
        return 0;
    }

    if(aFlag == 1)
    {
        for(int i=1; i < ktory; i++)
        {
            for(int j=0; j<dlugosci[i]; j++) printf("%c", tablica[i][j]);
            printf("\n");
        }
        return 0;
    }

    // przypadek bez flag
    srand(time(NULL));
    int random = (rand())%ktory;
    printf("%d\n", random);
    for(int j=0; j<dlugosci[random]; j++) printf("%c", tablica[random][j]);


    return 0;
}
