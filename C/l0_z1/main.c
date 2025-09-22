#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
    int n;
    bool czy;
    scanf("%d",&n);

    for(int j=n;;j++)
    {
        czy=1;
        for(int i=2;i*i<=j;i++)
        {
            if(j%(i*i) == 0)
            {
                czy=0;
                break;
            }
        }
        if(czy)
        {
            printf("%d",j);
            return 0;
        }
    }

    return 0;
}
