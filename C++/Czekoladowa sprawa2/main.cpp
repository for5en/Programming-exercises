#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

ll n,m,k;
ll silnia[1000005];
ll osilnia[1000005];
ll mod=1e9+7;
ll wynik,suma;
ll dp[1005][1005];

ll pot(ll a,ll b)
{
    ll odp=1;
    ll h=a;

    while(b>0)
    {
        //cout<<h<<"\n";
        if(b%2) odp*=h;
        h*=h;
        b/=2;
        if(odp>mod) odp%=mod;
        if(h>mod) h%=mod;
    }

    return odp;
}

void preprocess()
{
    silnia[0]=1;
    silnia[1]=1;

    bool czy=0;

    for(int i=2;i<=1000000;i++)
    {
        silnia[i]=silnia[i-1]*i;
        if(silnia[i]>mod) silnia[i]=silnia[i]%mod;
    }
    osilnia[1000000]=pot(silnia[1000000],mod-2);
    //cout<<silnia[1000000]<<"\n\n";
    for(int i=999999;i>=0;i--)
    {
        osilnia[i]=osilnia[i+1]*(i+1);
        osilnia[i]%=mod;
        //cout<<i<<": "<<osilnia[i]<<"\n";
    }
}

ll npok(ll a,ll b)
{
    //cout<<a<<" "<<b<<" "<<silnia[a]<<" "<<silnia[b]<<" "<<silnia[a-b]<<"\n";
    ll g=silnia[a];
    ll d=(osilnia[b]*osilnia[a-b]);
    if(d>mod) d%=mod;
    cout<<"npok "<<a<<" "<<b<<" = "<<g<<"/"<<d<<"\n";
    return ((g*d)%mod);
}

ll f(ll a, ll b)
{
    return dp[n][a+b];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    preprocess();

    cin>>n>>m>>k;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i>1) dp[i][j]=dp[i-1][j]*j;
            else dp[i][j]=1;
            if(i>1&&j>1) dp[i][j]+=dp[i-1][j-1]*j;
            cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(i+2*j<=k&&i+j<=n)
            {
                cout<<i<<" "<<j<<"\n";
                wynik=f(i,j)*f(i,j);
                wynik%=mod;
                cout<<wynik<<" ";

                wynik*=pot(i,n*(m-2));
                wynik%=mod;
                cout<<wynik<<" ";

                wynik*=npok(k,i);
                wynik%=mod;
                cout<<wynik<<" ";

                wynik*=npok(k-i,j);
                wynik%=mod;
                cout<<wynik<<" ";

                wynik*=npok(k-i-j,j);
                wynik%=mod;
                cout<<wynik<<" ";

                suma+=wynik;
                suma%=mod;
                cout<<suma<<" ";
            }
            cout<<"\n";
        }
    }

    cout<<suma;

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
