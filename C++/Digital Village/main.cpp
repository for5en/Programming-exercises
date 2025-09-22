#include <bits/stdc++.h>
#define ss second
#define ff first
#define pb push_back
#define ll long long

using namespace std;

int t;
int n,m,p;

int s;

int a,b,c;
vector < pair<int, pair<int,int>> > edges;

int rep[5005];
int ile[5005];

vector <int> reach[10005];
int wei[10005];
int cnt[10005];

void reset()
{
    while(!edges.empty()) edges.pop_back();
    for(int i=1;i<=10000;i++)
    {
        rep[i]=i;
        ile[i]=1;
    }
}

int Find(int x)
{
    while(x!=rep[x]) x=rep[x];
}

void Union(int x,int y,int z)
{
    x=Find(x);
    y=Find(y);

    if(ile[x]>ile[y]) swap(x,y);

    ile[y]+=ile[x];
    rep[x]=z;

    ile[z]=ile[y]+1;
    rep[y]=z;
}

void mst()
{
    int x,y,w;
    int id=n+1;

    for(int i=0;i<edges.size();i++)
    {
        x=edges[i].ss.ff;
        y=edges[i].ss.ss;
        w=edges[i].ff;

        if(Find(x) != Find(y))
        {
            x=Find(x);
            y=Find(y);
            reach[x].pb(id);
            reach[y].pb(id);

            reach[id].pb(x);
            reach[id].pb(y);

            cnt[id]=cnt[x]+cnt[y];
            wei[id]=w;

            Union(x,y,id);
            id++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    for(int ii=1; ii<=t; ii++)
    {
        cin>>n>>m>>p;
        reset();
        for(int i=1;i<=p;i++)
        {
            cin>>s;
            cnt[s]=1;
        }

        for(int i=1;i<=m;i++)
        {
            cin>>a>>b>>c;
            edges.pb({c,{a,b}});
        }

        sort(edges.begin(),edges.end());
        mst();

        for(int i=1;i<=2*n;i++)
        {
            cout<<i<<": ";
            for(int j=0;j<reach[i].size();j++)
            {
                cout<<reach[i][j]<<" ";
            }
            cout<<"\n";
            cout<<cnt[i]<<" "<<wei[i]<<"\n";
        }








    }

    return 0;
}

// Igor Rostkowski
// UWr isim 1
