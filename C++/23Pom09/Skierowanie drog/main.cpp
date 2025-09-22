#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m,t;
int aa,bb;
vector <int> graph[100010];
bitset <100010> odw;
vector <pair<int,int>> zap;

int poz[100010],moz[100010];
vector <int> tree[100010];
int p[100010],cykl[100010];
int num=1;

int rep[100010];
int ile[100010];

int Find(int a)
{
    while(a!=rep[a]) a=rep[a];
    return a;
}

void Union(int a,int b)
{
    if(ile[a]>ile[b]) swap(a,b);
    rep[a]=b;
}


queue <pair<int,int>> q;

map <pair<int,int>,char> mapk;


void genpoz(int x,int p)
{
    poz[x]=p;
    for(int i=0;i<graph[x].size();i++)
    {
        q.push({graph[x][i],p+1});
    }
}

void zcykl(int a,int b)
{
    int h=a;
    rep[a]=h;
    rep[b]=h;
    ile[h]=2;

    while(a!=b)
    {
        if(poz[a]>poz[b])
        {
            a=p[a];
            rep[a]=h;
            ile[h]++;
        }
        else
        {
            b=p[b];
            rep[b]=h;
            ile[h]++;
        }
    }
}

void dfs(int x,int r)
{
    //cout<<"dfs"<<x<<" "<<r<<"\n";
    odw[x]=1;
    p[x]=r;
    for(int i=0;i<graph[x].size();i++)
    {
        if(!odw[graph[x][i]])
        {
            dfs(graph[x][i],x);
        }
        else if(graph[x][i]!=r)
        {
            //cout<<"zykl"<<x<<" "<<graph[x][i]<<"\n";
            zcykl(x,graph[x][i]);
        }
    }
}

void polacz(int a,int b)
{
    int pa=a;
    int pb=b;

    while(a!=b)
    {
        //cout<<a<<" "<<poz[a]<<"   "<<b<<" "<<poz[b]<<"\n";
        if(poz[a]>poz[b])
        {
            pa=a;
            a=p[a];
            //cout<<"cykl   "<<Find(pa)<<" "<<Find(a)<<"\n";
            if(rep[a]==0||rep[pa]==0||Find(pa)!=Find(a))
            {
                //pa -> a
                //cout<<"zm  "<<a<<" "<<pa<<"\n";
                if(mapk[{pa,a}]=='B')
                {
                    mapk[{pa,a}]='R';
                }
                else
                {
                    mapk[{a,pa}]='L';
                }
            }
            Union(a,pa);
        }
        else
        {
            pb=b;
            b=p[b];
            if(rep[b]==0||rep[pb]==0||Find(b)!=Find(pb))
            {
                //pa -> a
                //cout<<"zm  "<<b<<" "<<pb<<"\n";
                if(mapk[{pb,b}]=='B')
                {
                    mapk[{pb,b}]='L';
                }
                else
                {
                    mapk[{b,pb}]='R';
                }
            }
            Union(b,pb);
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

        mapk[{aa,bb}]='B';
        graph[aa].pb(bb);
        graph[bb].pb(aa);
    }

    genpoz(1,1);

    while(!q.empty())
    {
        if(poz[q.front().ff]==0)
        {
            //cout<<"h";
            genpoz(q.front().ff,q.front().ss);
        }
        q.pop();
    }

    dfs(1,1);

    cin>>t;

    for(int i=1;i<=t;i++)
    {
        cin>>aa>>bb;
        if(Find(aa)!=Find(bb)||rep[aa]==0||rep[bb]==0)
        {
            //cout<<aa<<" "<<bb<<"\n";
            polacz(aa,bb);
            //cout<<"\n";
        }
    }

    for(int i=0;i<zap.size();i++)
    {
        cout<<mapk[{zap[i].ff,zap[i].ss}];
    }

    return 0;
}
