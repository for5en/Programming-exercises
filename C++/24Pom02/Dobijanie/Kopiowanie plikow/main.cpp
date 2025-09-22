#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,a,b;
int wx,wy;
int dpx[3000005],dpy[3000005];
vector <int> graph[3000005];
int skad[3000005];

vector <int> sciezka;

void dfsx(int x,int p)
{
    int mx=0;
    int mn=1e9;
    int sz=graph[x].size();
    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=p)
        {
            dfsx(graph[x][i],x);
            mn=min(mn,dpx[graph[x][i]]);
            mx=max(mx,dpx[graph[x][i]]);
        }
    }
    dpx[x]=max(mx+1, mn+sz-1);
}

void dfsy(int x,int p)
{
    skad[x]=p;

    int mx=0;
    int mn=1e9;
    int sz=graph[x].size();
    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=p)
        {
            dfsy(graph[x][i],x);
            mn=min(mn,dpy[graph[x][i]]);
            mx=max(mx,dpy[graph[x][i]]);
        }
    }
    dpy[x]=max(mx+1, mn+sz-1);
}

void updatedp(int x)
{

}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>wx>>wy;

    for(int i=1;i<n;i++)
    {
        cin>>a>>b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    dfsx(wx,wx);
    dfsy(wy,wy);

    int h=wx;
    while(h!=skad[h])
    {
        sciezka.pb(h);
        h=skad[h];
    }
    sciezka.pb(wy);
    h=sciezka.size();

    for(int i=0;i<h;i++)
    {
        cout<<sciezka[i]<<" ";
    }



    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
