#include <stdio.h>
#include <stdlib.h>

int n,m,d;
unsigned long long g[255][305],a,mx,odp,lic=0;

/*unsigned long long oblicz()
{
    odp=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            odp+=g[i][j];
        }
    }
    return odp;
}*/

unsigned long long podlanie(int x)
{
    odp=0;
    for(int i=1;i<=((x-1)%n)+1;i++)
    {
        for(int j=1;j<=m;j++)
        {
            odp+=g[i][j];
            if(g[i][j]%2 == 0)
            {
                g[i][j]/=2;
            }
            else if(g[i][j]!=0)
            {
                g[i][j]=3*g[i][j]+1;
            }
        }
    }
    for(int i=((x-1)%n)+2;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            odp+=g[i][j];
        }
    }
    lic+=n*m;
    return odp;
}

int main()
{
    scanf("%d%d%d",&n,&m,&d);

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%llu",&g[i][j]);
        }
    }

    for(int i=0;i<=d;i++)
    {
        a=podlanie(i+1);
        if(mx<a) mx=a;
        if(lic>=1e9) break;
    }

    printf("%llu",mx);

    return 0;
}
