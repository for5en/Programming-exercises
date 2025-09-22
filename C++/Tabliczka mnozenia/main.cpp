#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

ll m,k;

vector<ll> kopiec;
vector<pair<int,int>> pary;
int n;

void swp(int x, int y)
{
    swap(pary[x].ff, pary[y].ff);
    swap(pary[x].ss, pary[y].ss);
    swap(kopiec[x], kopiec[y]);
}

void pup(int x)
{
    while(kopiec[x/2] < kopiec[x] && x > 1)
    {
        swp(x/2, x);
        x /= 2;
    }
}

void pdown(int x)
{
    while(x*2 <= n)
    {
        int l = x*2;
        if(x*2+1 <= n && kopiec[l] < kopiec[x*2+1]) l = x*2+1;
        if(kopiec[x] < kopiec[l]) swp(l, x), x=l;
        else break;
    }
}

void add(ll a, ll b)
{
    //cout<<a<<" "<<b<<"\n";
    while(kopiec.size() < n+2) kopiec.pb(0);
    while(pary.size() < n+2) pary.pb({0,0});
    n++;
    pary[n] = {a, b};
    kopiec[n] = a*b;
    pup(n);
}

void delmax()
{
    ll a = pary[1].ff;
    ll b = pary[1].ss;
    swp(1, n);
    kopiec[n] = 0;
    pary[n].ff = 0;
    pary[n].ss = 0;
    pdown(1);
    n--;

    add(a-1, b-1);
    if(a == m) add(a, b-1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll pop=0;

    cin>>m>>k;

    add(m, m);

    for(int i=1; i<=k; i++)
    {
        while(kopiec[1] == pop)
        {
            delmax();
        }
        cout<<kopiec[1]<<"\n";
        pop = kopiec[1];
        delmax();
    }

    return 0;
}
