#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

ll n,m,k,wynik;
ll mod=1000000007;
ll dp; // i-s, j-wsp
ll silnia[1000005];

void preprocess()
{
    silnia[0]=1;
    silnia[1]=1;
    for(int i=2;i<=1000000;i++)
    {
        silnia[i]=silnia[i-1]*i;
        if(silnia[i]>mod) silnia[i]%=mod;
    }
}

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

ll npok(ll a,ll b)
{
    //cout<<a<<" "<<b<<" "<<silnia[a]<<" "<<silnia[b]<<" "<<silnia[a-b]<<"\n";
    ll g=silnia[a];
    ll d=(silnia[b]*silnia[a-b]);
    if(d>mod) d%=mod;
    d=pot(d,mod-2);
    if(d>mod) d%=mod;

    return ((g*d)%mod);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>k;

    preprocess();

    //cout<<pot(3,5);

    if(m==2)
    {
        wynik+=k;
        wynik+=npok(k,2)*2;
        for(int i=2;i<=k;i++) //ile kolorow
        {
            //cout<<i<<"\n";
            if(n>=i) wynik+=npok(n,i)*npok(n,i)*npok(k,i)*npok(k,i)*silnia[i]*silnia[i]*silnia[n-i]*silnia[n-i];
        }
        cout<<wynik;
        return 0;
    }
    if(k<3)
    {
        wynik+=k+npok(3,2)*npok(k,2)*2*npok(3,2)*npok(k,2)*2;
        cout<<wynik;
        return 0;
    }

    for(int i=1;i<=n;i++) // s
    {
        for(int j=1;j<=i;j++) // wsp
        {
            if(j+2*n-2*i>0&&j+2*n-2*i<=k)
            {
                dp=npok(n,i)*npok(n,i);
                if(dp>mod) dp%=mod;
                dp*=npok(i,j);
                if(dp>mod) dp%=mod;
                dp*=npok(i,j);
                if(dp>mod) dp%=mod;
                dp*=silnia[j];
                if(dp>mod) dp%=mod;
                dp*=silnia[j];
                if(dp>mod) dp%=mod;
                dp*=pot(j,i-j);
                if(dp>mod) dp%=mod;
                dp*=pot(j,i-j);
                if(dp>mod) dp%=mod;
                dp*=npok(k,j);
                if(dp>mod) dp%=mod;
                dp*=npok(k-j,n-i);
                if(dp>mod) dp%=mod;
                dp*=npok(k-j-n+i,n-i);
                if(dp>mod) dp%=mod;
                if(m>2) dp*=pot(j,(m-2)*n);
                if(dp>mod) dp%=mod;
                //cout<<dp<<" ";
                wynik+=dp;
                //cout<<dp<<"\n";
                if(wynik>mod) wynik%=mod;
            }
            else
            {
                //cout<<"nie da sie ";
            }
        }
        //cout<<"\n";
    }

    cout<<wynik;

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
