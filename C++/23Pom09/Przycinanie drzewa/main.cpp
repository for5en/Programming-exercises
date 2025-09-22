#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,odp;
int a[300010];
int ilec[300010],ilen[300010];
int cc,nn;
int p,k;

vector <int> graph[300010];

void dfs(int x,int r)
{
    if(a[x]==1)
    {
        ilec[x]++;
    }
    else if(a[x]==2)
    {
        ilen[x]++;
    }

    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=r)
        {
            dfs(graph[x][i],x);
            ilec[x]+=ilec[graph[x][i]];
            ilen[x]+=ilen[graph[x][i]];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }

    for(int i=1;i<n;i++)
    {
        cin>>p>>k;
        graph[p].pb(k);
        graph[k].pb(p);
    }

    dfs(1,0);

    cc=ilec[1];
    nn=ilen[1];

    for(int i=2;i<=n;i++)
    {
        if((cc-ilec[i]==0||nn-ilen[i]==0)&&(ilec[i]==0||ilen[i]==0))
        {
            odp++;
        }
    }

    cout<<odp;

    return 0;
}
