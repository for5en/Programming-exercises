#include <stdlib.h>
#include <stdio.h>
#include "sortlib.h"

void sortowanie(char*** tab, __compar_fn_t komp)
{
    #ifdef USE_QSORT
        int id = 0;
        while(tab[id] != NULL) id++;

        printf("QSORT:\n");
        qsort(tab, id, sizeof(char**), (__compar_fn_t) komp);
    #else
        char** h;
        printf("BABELKOWE:\n");
        for(int i=0; tab[i]!=NULL; i++)
        {
            for(int j=0; tab[j]!=NULL; j++)
            {
                if(komp(&tab[i], &tab[j]) == -1)
                {
                    h = tab[i];
                    tab[i] = tab[j];
                    tab[j] = h;
                }
            }
        }
    #endif

}