#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m,aa,bb,q;
int gle[100010],low[100010];
vector <int> graph[100010];
int p[100010];
bitset <100010> odw;
vector <pair<int,int>> zap;
vector <int> kor;

int ile[100010];

map <pair<int,int>,char> kr;

void dfstree(int x,int r)
{
    low[x]=gle[x];
    odw[x]=1;
    p[x]=r;

    for(int i=0;i<graph[x].size();i++)
    {
        if(!odw[graph[x][i]])
        {
            gle[graph[x][i]]=gle[x]+1;
            dfstree(graph[x][i],x);
            low[x]=min(low[x],low[graph[x][i]]);
        }
        else if(graph[x][i]!=r)
        {
            low[x]=min(low[x],gle[graph[x][i]]);
        }
    }
}

void dodaj(int a,int b)
{
    //a->b
    if(kr.find({a,b})!=kr.end())
    {
        kr[{a,b}]='L';
    }
    else
    {
        kr[{b,a}]='R';
    }
}

void dfs(int x,int r)
{
    odw[x]=1;
    //cout<<x<<"\n";

    for(int i=0;i<graph[x].size();i++)
    {
        if(!odw[graph[x][i]]&&graph[x][i]!=r)
        {
            dfs(graph[x][i],x);
            ile[x]+=ile[graph[x][i]];
        }
    }
    if(low[x]==gle[x])
    {
        //cout<<low[x]<<" "<<gle[x]<<" "<<ile[x]<<"\n";
        if(ile[x]>0)
        {
            dodaj(p[x],x);
        }
        else if(ile[x]<0)
        {
            dodaj(x,x[p]);
        }
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
        cin>>aa>>bb;
        zap.pb({aa,bb});
        graph[aa].pb(bb);
        graph[bb].pb(aa);
        kr[{aa,bb}]='B';
    }

    for(int i=1;i<=n;i++)
    {
        if(!odw[i])
        {
            low[i]=1;
            gle[i]=1;
            dfstree(i,1);
            kor.pb(i);
        }
    }
    odw=0;

    cin>>q;

    for(int i=1;i<=q;i++)
    {
        cin>>aa>>bb;
        ile[aa]++;
        ile[bb]--;
    }

    for(int i=0;i<kor.size();i++)
    {
        dfs(kor[i],1);
    }

    for(int i=0;i<zap.size();i++)
    {
        cout<<kr[{zap[i].ff,zap[i].ss}];
    }
    cout<<"\n";



    return 0;
}
