#include <stdio.h>
#include <stdlib.h>

int a,b,c,d,n,h;



void shift()
{
    if(a<b)
    {
        h=a;
        a=b;
        b=h;
    }
    if(b<c)
    {
        h=b;
        b=c;
        c=h;
    }
    if(a<b)
    {
        h=a;
        a=b;
        b=h;
    }
}

int ile(int x)
{
    int odp=0;
    for(int i=3;i<=x;i+=2)
    {
        if(x%i==0)
        {
            //printf("%d\n",i);
            odp++;
            while(x%i==0) x/=i;
        }
    }
    return odp;
}

int main()
{
    scanf("%d%d%d%d",&n,&a,&b,&c);

    for(int i=1;i<=n-3;i++)
    {
        scanf("%d",d);
        if(d<a) a=d;
        shift();
    }
    if(ile(a)>ile(b) && ile(a)>ile(b)) printf("%d",a);
    else if(ile(b)>ile(a) && ile(b)>ile(c)) printf("%d",b);
    else printf("%d",c);


    return 0;
}
