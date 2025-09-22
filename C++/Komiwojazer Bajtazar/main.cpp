#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m;
int a,b;
int tab[5005];

vector <int> graph[30005];
int gle[30005];
int jump[30005][16];


void genjump(int x,int p)
{
    jump[x][0]=p;
    gle[x]=gle[p]+1;

    for(int i=1;i<=15;i++)
    {
        if((1<<i)<=gle[x])
        {
            jump[x][i] = jump[jump[x][i-1]][i-1];
        }
    }

    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=p) genjump(graph[x][i],x);
    }
}

int lca(int x,int y)
{
    if(gle[x]<gle[y]) swap(x,y);
    //gle[x] > gle[y]

    for(int i=15;i>=0;i--)
    {
        if(gle[x]-(1<<i) >= gle[y]) x=jump[x][i];
    }

    if(x==y) return x;

    for(int i=15;i>=0;i--)
    {
        if(gle[x]>=(1<<i))
        {
            if(jump[x][i]!=jump[y][i])
            {
                x=jump[x][i];
                y=jump[y][i];
            }
        }
    }

    return jump[x][0];
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

    cin>>m;

    for(int i=1;i<=m;i++)
    {
        cin>>tab[i];
    }

    gle[0]=-1;
    genjump(1,0);
    /*for(int i=1;i<=n;i++)
    {
        cout<<i<<":  ";
        for(int j=0;j<=15;j++) cout<<jump[i][j]<<" ";
        cout<<"\n";
    }*/

    int h=1;
    int p=0;
    int odp=0;

    //cout<<"\n";
    for(int i=1;i<=m;i++)
    {
        p=lca(h,tab[i]);
        odp=odp+abs(gle[h]-gle[p])+abs(gle[tab[i]]-gle[p]);
        //cout<<p<<" "<<odp<<"\n";
        h=tab[i];
    }

    cout<<odp;


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
