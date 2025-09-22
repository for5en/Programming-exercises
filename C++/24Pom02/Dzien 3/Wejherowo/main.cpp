#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,a,b;
vector <int> graph[100005];
int pod[100005];
ll odpmax,odpmin;

void dfs(int x,int r)
{
    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=r)
        {
            dfs(graph[x][i],x);
            odpmax+=min(pod[graph[x][i]],n-pod[graph[x][i]]);
            pod[x]+=pod[graph[x][i]];
        }
    }
    pod[x]++;
}

bool dfs2(int x,int r)
{
    ll ile=0;
    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=r)
        {
            ile+=dfs2(graph[x][i],x);
        }
    }
    odpmin+=ile;
    //cout<<x<<" "<<ile<<"\n";
    if(graph[x].size()==1 && x!=1) return 1;
    else if(ile%2) return 0;
    else return 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<n;i++)
    {
        cin>>a>>b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    dfs(1,0);
    ll h=dfs2(1,0);
    odpmin+=h;
    cout<<odpmin*2<<" "<<odpmax*2;
    //for(int i=1;i<=n;i++) cout<<pod[i]<<" ";

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
