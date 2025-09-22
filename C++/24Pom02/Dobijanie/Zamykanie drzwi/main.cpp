#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m,odp;
int a,b;
vector <int> tops;
vector <int> graph[100005];
vector <int> rgraph[100005];
vector <int> sssgraph[100005];
int rep[100005];
int num;

bitset <100005> odw;

void toposort(int x)
{
    odw[x]=1;
    for(int i=0;i<graph[x].size();i++)
    {
        if(!odw[graph[x][i]]) toposort(graph[x][i]);
    }
    tops.pb(x);
}

void kosaraju(int x)
{
    rep[x]=num;
    for(int i=0;i<rgraph[x].size();i++)
    {
        if(rep[rgraph[x][i]]==0) kosaraju(rgraph[x][i]);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        graph[b].pb(a);
        rgraph[a].pb(b);
    }

    for(int i=1;i<=n;i++)
    {
        if(!odw[i]) toposort(i);
    }

    //for(int i=0;i<n;i++) cout<<tops[i]<<" ";
    //cout<<"\n";

    for(int i=tops.size()-1;i>=0;i--)
    {
        if(rep[tops[i]]==0) num++, kosaraju(tops[i]);
    }

    //for(int i=1;i<=n;i++) cout<<rep[i]<<" ";
    //cout<<"\n";

    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<graph[i].size();j++)
        {
            if(rep[i]!=rep[graph[i][j]])
            {
                //cout<<rep[i]<<" -> "<<rep[graph[i][j]]<<"\n";
                sssgraph[rep[i]].pb(rep[graph[i][j]]);
            }
        }
    }

    for(int i=1;i<=num;i++)
    {
        if(sssgraph[i].size()==0) odp++;
    }

    cout<<odp;

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
