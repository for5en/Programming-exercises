#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m;
int aa,bb;

vector <int> graph[100005];
bitset <100005> odw;

vector <int> wst[100005];
int low[100005],gle[100005],p[100005];
bool k[100005];
bool odp;

void dfstree(int x,int r)
{
    odw[x]=1;
    p[x]=r;
    gle[x]=gle[r]+1;
    low[x]=gle[x];
    k[x]=!k[r];

    for(int i=0;i<graph[x].size();i++)
    {
        if(!odw[graph[x][i]])
        {
            dfstree(graph[x][i],x);
            low[x]=min(low[x],low[graph[x][i]]);
        }
        else if(graph[x][i]!=p[x]&&gle[x]>gle[graph[x][i]])
        {
            low[x]=min(low[x],gle[graph[x][i]]);
            //cout<<x<<" "<<k[x]<<"   "<<graph[x][i]<<" "<<k[graph[x][i]]<<"\n";
            if(k[x]==!k[graph[x][i]])
            {
                odp=1;
            }
            else if(low[graph[x][i]]<gle[graph[x][i]])
            {
                odp=1;
            }
            wst[x].pb(graph[x][i]);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=0;i<m;i++)
    {
        cin>>aa>>bb;
        graph[aa+1].pb(bb+1);
        graph[bb+1].pb(aa+1);
    }

    for(int i=1;i<=n;i++)
    {
        if(!odw[i]) dfstree(i,0);
    }

    if(odp) cout<<"JEST";
    else cout<<"BRAK";


    return 0;
}
