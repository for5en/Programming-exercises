#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,gx,gy;
int a,b;
vector <int> graph[3000005];

int timex[3000005],timey[3000005];

void dfsx(int x,int r)
{
    int mn=99999999;
    int mx=0;
    int sz=graph[x].size();
    for(int i=0;i<sz;i++)
    {
        if(graph[x][i]!=r)
        {
            dfsx(graph[x][i],x);
            mx=max(mx,timex[graph[x][i]]);
            mn=min(mn,timex[graph[x][i]]);
        }
    }
    timex[x]=max(mx+1,mn+sz-1);
    if(graph[x].size()==1) timex[x]=1;
    if(x==gx) timex[x]=max(mx,mn+sz-1);
}

void dfsy(int x,int r)
{
    int mn=99999999;
    int mx=0;
    int sz=graph[x].size();
    for(int i=0;i<sz;i++)
    {
        if(graph[x][i]!=r)
        {
            dfsy(graph[x][i],x);
            mx=max(mx,timey[graph[x][i]]);
            mn=min(mn,timey[graph[x][i]]);
        }
    }
    timey[x]=max(mx+1,mn+sz-1);
    if(graph[x].size()==1) timey[x]=1;
    if(x==gy) timey[x]=max(mx,mn+sz-1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>gx>>gy;

    for(int i=1;i<n;i++)
    {
        cin>>a>>b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    dfsx(gx,0);
    dfsy(gy,0);

    for(int i=1;i<=n;i++)
    {
        cout<<timex[i]<<" "<<timey[i]<<"\n";
    }


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
