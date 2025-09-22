#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,l,m;
int a,b,p1,p2;

string s;

pair <ll,ll> hasze[1005];
pair <ll,ll> pot[105];
pair <ll,ll> mod={1e9+7,1e9+9};

map < pair<ll,ll> ,int > ilosc;
map < pair<ll,ll> ,int > wynik;

int odp[1005];

void preprocess()
{
    pot[0]={1,1};

    for(int i=1;i<=100;i++)
    {
        pot[i].ff=pot[i-1].ff*29;
        pot[i].ss=pot[i-1].ss*31;

        if(pot[i].ff>mod.ff) pot[i].ff%=mod.ff;
        if(pot[i].ss>mod.ss) pot[i].ss%=mod.ss;
    }
}

pair <ll,ll> haszuj(string str)
{
    pair <ll,ll> odp={0,0};

    for(int i=0;i<str.size();i++)
    {
        odp.ff+=pot[i].ff*(str[i]);
        odp.ss+=pot[i].ss*(str[i]);

        if(odp.ff>mod.ff) odp.ff%=mod.ff;
        if(odp.ss>mod.ss) odp.ss%=mod.ss;
    }

    return odp;
}

void zmiana(int px, int x, int py, int y)
{
    ilosc[hasze[px]]--;
    ilosc[hasze[py]]--;

    hasze[px]-=hasze[]
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>l>>m;
    preprocess();

    for(int i=1;i<=n;i++)
    {
        cin>>s;
        hasze[i]=haszuj(s);
        ilosc[hasze[i]]++;
    }

    for(int i=1;i<=m;i++)
    {
        cin>>p1>>a>>p2>>b;
    }


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
