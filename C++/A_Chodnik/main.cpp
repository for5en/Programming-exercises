#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
int l,m,r;
bool notFind = 1;
int ile;

vector <pair<int,int>> graph[10010];
pair<int,int> skad[10010];
bool odw[10010];

void dfs(int x)
{
    odw[x]=1;
    for(int i=0;i<graph[x].size();i++)
    {
        if(!odw[graph[x][i].ff])
        {
            skad[graph[x][i].ff] = {x,graph[x][i].ss};
            dfs(graph[x][i].ff);
        }
    }
}

void rek(int x)
{
    ile++;
    if(x == 0)
    {
        cout<<ile-1<<"\n";
        return;
    }
    rek(skad[x].ff);

    if(x == 10001) cout<<skad[x].ff<<" "<<skad[x].ss<<" 0\n";
    else cout<<skad[x].ff<<" "<<skad[x].ss<<" "<<x<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>l>>m>>r;
        if(r!=0) graph[l].pb({r,m});
        else graph[l].pb({10001,m});
    }

    dfs(0);
    if(!odw[10001])
    {
        cout<<"BRAK";
        return 0;
    }
    //cout<<"\n";
    rek(10001);


    return 0;
}
