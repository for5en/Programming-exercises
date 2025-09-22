#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

ll wynik[1000105];
ll h;
ll n;
ll a,b;
pair<ll,ll> zlo[1000105]; // ff-poczatek, ssff-koniec, ssss-numer
map <ll,ll> mapa;
vector <ll> lic;
vector <pair<ll,pair<ll,ll>>> v;

ll base=(1<<21), tree[(1<<22)];
void update(ll gdzie,ll ile)
{
    gdzie+=base;
    gdzie--;
    tree[gdzie]=ile;
    while(gdzie>0)
    {
        gdzie/=2;
        tree[gdzie]=max(tree[gdzie*2],tree[gdzie*2+1]);
    }
}
ll query(ll gdzie,ll p,ll k,ll x,ll y)
{
    if(x<=p&&k<=y) return tree[gdzie];

    ll sr=(p+k)/2;
    ll odp=0;

    if(x<=sr) odp=query(gdzie*2,p,sr,x,y);
    if(sr<y) odp=max(odp,query(gdzie*2+1,sr+1,k,x,y));

    return odp;
}

bool comp(pair<ll,pair<ll,ll>> x,pair<ll,pair<ll,ll>> y)
{
    if(x.ff==y.ff) return (y.ss.ff<x.ss.ff);
    else return (x.ff<y.ff);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(ll i=1;i<=n;i++)
    {
        cin>>a>>b;
        zlo[i]={a,a+b};
        lic.pb(a);
        lic.pb(a+b);
    }
    // skalowanie
    sort(lic.begin(),lic.end());
    ll num=2;
    mapa[lic[0]]=1;
    for(ll i=1;i<lic.size();i++)
    {
        if(lic[i]!=lic[i-1])
        {
            mapa[lic[i]]=num;
            num++;
        }
    }

    for(ll i=1;i<=n;i++)
    {
        v.pb({mapa[zlo[i].ss],{mapa[zlo[i].ff],i}});
        //cout<<zlo[i].ss<<" "<<mapa[zlo[i].ff]<<" "<<i<<"\n";
    }
    sort(v.begin(),v.end(),comp);

    /*for(ll i=0;i<v.size();i++)
    {
        cout<<v[i].ff<<" "<<v[i].ss.ff<<" "<<v[i].ss.ss<<"\n";
    }*/

    for(ll i=v.size()-1;i>=0;i--)
    {
        h=query(1,1,base,1,v[i].ss.ff)+1;
        wynik[v[i].ss.ss]=h;
        //cout<<h<<"\n";
        update(v[i].ss.ff,h);
    }

    for(ll i=1;i<=n;i++)
    {
        cout<<wynik[i]-1<<" ";
    }


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
