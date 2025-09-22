#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m;
char c;

bool tab[1510][1510];
int dpd1[1510][1510],dpd2[1510][1510]; // down v
int dpu1[1510][1510],dpu2[1510][1510]; // up ^
int dpr1[1510][1510],dpr2[1510][1510]; // right ->
int dpl1[1510][1510],dpl2[1510][1510]; // left <-
// dp1 - aktualnie najdluzsze, dp2 - poprzednio najdluzsze

int odpm1,odpm2;

int mxpio(int x)
{
    return max(dpu1[1][x],dpu2[1][x]);
}

int mxpoz(int x)
{
    return max(dpr1[x][n],dpr2[x][n]);
}

void dpd()
{
    int a,mxa,mxp;

    for(int i=1;i<=n;i++)
    {
        a=0;
        mxa=0;
        mxp=0;

        for(int j=1;j<=n;j++)
        {
            if(tab[j][i])
            {
                a++;
                mxa=max(mxa,a);
            }
            else
            {
                a=0;
                mxp=mxa;
            }
            dpd1[j][i]=a;
            dpd2[j][i]=mxp;
            odpm1=max(odpm1,a);
        }
    }
}

void dpu()
{
    int a,mxa,mxp;

    for(int i=1;i<=n;i++)
    {
        a=0;
        mxa=0;
        mxp=0;

        for(int j=n;j>=1;j--)
        {
            if(tab[j][i])
            {
                a++;
                mxa=max(mxa,a);
            }
            else
            {
                a=0;
                mxp=mxa;
            }
            dpu1[j][i]=a;
            dpu2[j][i]=mxp;
            odpm1=max(odpm1,a);
        }
    }
}

void dpr()
{
    int a,mxa,mxp;

    for(int i=1;i<=n;i++)
    {
        a=0;
        mxa=0;
        mxp=0;

        for(int j=1;j<=n;j++)
        {
            if(tab[i][j])
            {
                a++;
                mxa=max(mxa,a);
            }
            else
            {
                a=0;
                mxp=mxa;
            }
            dpr1[i][j]=a;
            dpr2[i][j]=mxp;
            odpm1=max(odpm1,a);
        }
    }
}

void dpl()
{
    int a,mxa,mxp;

    for(int i=1;i<=n;i++)
    {
        a=0;
        mxa=0;
        mxp=0;

        for(int j=n;j>=1;j--)
        {
            if(tab[i][j])
            {
                a++;
                mxa=max(mxa,a);
            }
            else
            {
                a=0;
                mxp=mxa;
            }
            dpl1[i][j]=a;
            dpl2[i][j]=mxp;
            odpm1=max(odpm1,a);
        }
    }
}

int dpmx(int x,int y)
{
    int o1,o2,r,odp;
    o1=0;
    o2=0;
    r=0;

    ////////////////////////////////////
    // 2 POPRZEDNIE NAJDLUZSZE

    if(o1<dpd2[x][y])
    {
        o1=dpd2[x][y];
        if(o2<o1) swap(o1,o2);
    }
    if(o1<dpu2[x][y])
    {
        o1=dpu2[x][y];
        if(o2<o1) swap(o1,o2);
    }
    if(o1<dpr2[x][y])
    {
        o1=dpr2[x][y];
        if(o2<o1) swap(o1,o2);
    }
    if(o1<dpl2[x][y])
    {
        o1=dpl2[x][y];
        if(o2<o1) swap(o1,o2);
    }

    odp=min(o1,o2);


    ////////////////////////////////////
    // AKTUALNY POZIOMY/PIONOWY I POPRZEDNIO NAJDLUZSZY

    r=max(dpd1[x][y]+dpu1[x][y]-1,dpr1[x][y]+dpl1[x][y]-1);
    odp=max(odp,min(o2,r));

    ////////////////////////////////////
    // AKTUALNE PIONOWE

    o1=dpd1[x][y]-1;
    o2=dpu1[x][y]-1;
    if(o2<o1) swap(o1,o2);
    o1++;

    odp=max(odp,min(o1,o2));

    ////////////////////////////////////
    // AKTUALNE POZIOME

    o1=dpl1[x][y]-1;
    o2=dpr1[x][y]-1;
    if(o2<o1) swap(o1,o2);
    o1++;

    odp=max(odp,min(o1,o2));

    ////////////////////////////////////
    // AKTUALNA POZIOMA Z PIONOWA

    o1=max(dpl1[x][y],dpr1[x][y])-1;
    o2=max(dpu1[x][y],dpd1[x][y])-1;
    if(o2<o1) swap(o1,o2);
    o1++;

    odp=max(odp,min(o1,o2));

    ////////////////////////////////////
    // WYPISYWANIE WYNIKU :DD

    return odp;
}

int mxdprl()
{
    int o1,o2,odp;
    o1=0;
    o2=0;
    odp=0;

    for(int i=1;i<=n;i++)
    {
        if(o1<mxpoz(i))
        {
            o1=mxpoz(i);
            if(o2<o1) swap(o1,o2);
        }
    }

    odp=min(o1,o2);

    o1=0;
    o2=0;
    for(int i=1;i<=n;i++)
    {
        if(o1<mxpio(i))
        {
            o1=mxpio(i);
            if(o2<o1) swap(o1,o2);
        }
    }

    odp=max(odp,min(o1,o2));

    return odp;
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
            cin>>c;
            if(c=='.') tab[i][j]=1;
        }
    }

    dpd();
    dpu();
    dpr();
    dpl();

    // m = 1 - jeden pas

    if(m==1)
    {
        cout<<odpm1;
        return 0;
    }

    // m = 2 - dwa pasy

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            odpm2=max(odpm2,dpmx(i,j));
        }
    }

    cout<<max(mxdprl(),odpm2);










    /*for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<dpl1[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<dpl2[i][j]<<" ";
        }
        cout<<"\n";
    }*/



    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
