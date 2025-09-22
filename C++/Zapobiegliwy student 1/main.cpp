#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,odp;
int a,b;

int po[500005];
vector <pair<int,int>> v;
//.ff - czas
//.ss - numer

int ile,k;
int x,y;

vector <int> g;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;

        po[i]=a;
        v.pb({b,i});
    }

    sort(v.begin(),v.end());

    for(int i=0;i<v.size();i++)
    {
        if(po[v[i].ss]>=k)
        {
            k=v[i].ff;
            odp++;
            g.pb(v[i].ss);
        }
    }

    cout<<odp-1<<"\n";

    for(int i=0;i<g.size()-1;i++)
    {
        cout<<g[i]<<" "<<g[g.size()-1]<<"\n";
    }

    return 0;
}
