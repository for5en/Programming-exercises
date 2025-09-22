#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int n,t,h,sum;
int c[1000010];
int d[1000010];

int main()
{

    scanf("%d%d",&n,&c[1]);
    for(int i=2;i<n;i++)
    {
        scanf("%d",&c[i]);
    }

    d[n]=1;
    for(int i=n-1;i>=1;i--)
    {
        if(c[i]==-1) d[i]=d[i+1]+1;
        else d[i]=1;
    }

    h=0;
    c[0]=1;
    for(int i=1;i<=n;i++)
    {
        if(d[i]==0)
        {
            h=h+1;
        }
        else
        {
            if(c[i-1]==1)
            {
                if(h+1>d[i]) h = h+1;
                else h = d[i];
                //h=__max(h+1,d[i]);
            }
            else
            {
                h=d[i];
            }
        }
        printf("%d ",h);
    }

    return 0;
}
