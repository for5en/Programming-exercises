#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    char* tab[n+1];

    for(int i=1;i<=n;i++)
    {
        //printf("%d ",i);
        tab[i] = calloc(60,sizeof(char));
        fgets(tab[i], 55, stdin);
    }

    int liczba[55];
    liczba[50] = 0;

    for(int i=50;i>=1;i--)
    {
        liczba[i-1]=0;
        for(int j=1;j<=n;j++)
        {
            liczba[i] += (int)(tab[j][i-1] - '0');
            //printf("%c ", tab[j][i-1]);
        }
        //printf("%d ", liczba[i]);
        //printf("\n");
        liczba[i-1] += (liczba[i]/10);
        liczba[i] %= 10;
    }
    //printf("\n");

    if(liczba[0] == 0)
    {
        for(int i=1;i<=9;i++) printf("%d", liczba[i]);
    }
    else
    {
        for(int i=0;i<=8;i++) printf("%d", liczba[i]);
    }

    return 0;
}