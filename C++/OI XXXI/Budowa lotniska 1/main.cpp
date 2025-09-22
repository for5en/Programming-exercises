#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m;
int mx1,mx2;
char ch;

bool tab[1505][1505];
//plan lotniska

int c[1505];
//max kolumn

int r[1505];
//max wierszy

int odp,odph;

int maxc,maxr;

//dpki
int tla[1505][1505],tlb[1505][1505]; //left
int tra[1505][1505],trb[1505][1505]; //right
int tua[1505][1505],tub[1505][1505]; //up
int tda[1505][1505],tdb[1505][1505]; //down


int maxcr()
{
    int a=0;
    int mx=0;

    //max kolumn
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(tab[j][i]) a++;
            else
            {
                c[i]=max(c[i],a);
                mx=max(mx,a);
                a=0;
            }
        }
        c[i]=max(c[i],a);
        mx=max(mx,a);
        a=0;
    }

    //max wierszy
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(tab[i][j]) a++;
            else
            {
                r[i]=max(r[i],a);
                mx=max(mx,a);
                a=0;
            }
        }
        r[i]=max(r[i],a);
        mx=max(mx,a);
        a=0;
    }

    return mx;
}

void tleft()
{
    int a=0;
    int b=0;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(tab[i][j])
            {
                a++;
            }
            else
            {
                b=max(b,a);
                a=0;
            }
            tla[i][j]=a;
            tlb[i][j]=b;
        }
        a=0;
        b=0;
    }
}

void tright()
{
    int a=0;
    int b=0;

    for(int i=1;i<=n;i++)
    {
        for(int j=n;j>=1;j--)
        {
            if(tab[i][j])
            {
                a++;
            }
            else
            {
                b=max(b,a);
                a=0;
            }
            tra[i][j]=a;
            trb[i][j]=b;
        }
        a=0;
        b=0;
    }
}

void tup()
{
    int a=0;
    int b=0;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(tab[j][i])
            {
                a++;
            }
            else
            {
                b=max(b,a);
                a=0;
            }
            tua[j][i]=a;
            tub[j][i]=b;
        }
        a=0;
        b=0;
    }
}

void tdown()
{
    int a=0;
    int b=0;

    for(int i=1;i<=n;i++)
    {
        for(int j=n;j>=1;j--)
        {
            if(tab[j][i])
            {
                a++;
            }
            else
            {
                b=max(b,a);
                a=0;
            }
            tda[j][i]=a;
            tdb[j][i]=b;
        }
        a=0;
        b=0;
    }
}

int sec(int a1,int a2,int a3,int a4)
{
    if(a1>a2) swap(a1,a2);
    if(a3>a4) swap(a3,a4);
    if(a2>a3) swap(a2,a3);
    if(a1>a2) swap(a1,a2);
    if(a3>a4) swap(a3,a4);

    return a3;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>ch;
            if(ch=='.')
            {
                tab[i][j]=1;
            }
        }
    }

    mx1=maxcr();


    //DLA M=1
    /////////////////////////////////////////////////////////////////////////////////////

    if(m==1)
    {
        cout<<mx1;
        return 0;
    }


    //DLA M=2
    /////////////////////////////////////////////////////////////////////////////////////


    //PASY ROWNOLEGLE
    for(int i=2;i<=n;i++)
    {
        maxc=max(maxc,c[i-1]);
        odp=max(odp,min(maxc,c[i]));
    }

    for(int i=2;i<=n;i++)
    {
        maxr=max(maxr,r[i-1]);
        odp=max(odp,min(maxr,r[i]));
    }


    //PASY PROSTOPADLE
    tleft();
    tright();
    tup();
    tdown();

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(tab[i][j])
            {
                //wspoliniowe poziome
                odph=max(odph,min(tla[i][j]+tra[i][j]-1,tlb[i][j]));
                odph=max(odph,min(tla[i][j]+tra[i][j]-1,trb[i][j]));

                odph=max(odph,(tla[i][j]+tra[i][j]-1)/2);

                //wspolliniowe pionowe
                odph=max(odph,min(tua[i][j]+tda[i][j]-1,tub[i][j]));
                odph=max(odph,min(tua[i][j]+tda[i][j]-1,tdb[i][j]));

                odph=max(odph,(tua[i][j]+tda[i][j]-1)/2);

                // prostopadle a-poziome
                odph=max(odph,min(tla[i][j]+tra[i][j]-1,tub[i][j]));
                odph=max(odph,min(tla[i][j]+tra[i][j]-1,tdb[i][j]));

                odph=max(odph,min(tla[i][j]+tra[i][j]-1,max(tda[i][j],tua[i][j])-1));

                // prostopadle a-pionowe
                odph=max(odph,min(tua[i][j]+tda[i][j]-1,tlb[i][j]));
                odph=max(odph,min(tua[i][j]+tda[i][j]-1,trb[i][j]));

                odph=max(odph,min(tua[i][j]+tda[i][j]-1,max(tra[i][j],tla[i][j])-1));

                //rozlaczne w punkcie P(i,j) - [+]
                //cout<<sec(tua[i][j],tda[i][j],tla[i][j],tra[i][j])-1<<" "<<i<<" "<<j<<"\n";
                //odph=max(odph,sec(tua[i][j],tda[i][j],tla[i][j],tra[i][j])-1);
            }
            else
            {
                //prostopadle b - rozlaczne
                odph=max(odph,min(max(tub[i][j],tdb[i][j]),max(tlb[i][j],trb[i][j])));
            }
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<tlb[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<trb[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<tub[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<tdb[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";

    cout<<max(odp,odph);



    return 0;
}

//Igor Rostkowski
//lo3 Gdynia 4EP
