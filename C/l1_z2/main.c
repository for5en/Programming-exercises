#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int ile(int m)
{
    int c,w=0;
    for(int i=1;i<m;i++)
    {
        for(int j=i;j<m;j++)
        {
            c=m-i-j;
            if(i+j > c && i+c > j && j+c > i && i*i+j*j == c*c) w++;
        }
    }
    return w;
}

int main()
{
    int n,mx,t;
    scanf("%d",&n);
    mx=0;

    for(int i=12;i<=n;i++)
    {
        //printf("%d", ile(i));
        if(ile(i)>mx)
        {
            mx=ile(i);
            t=i;
        }
    }

    printf("%d %d", t, mx);


    return 0;
}
