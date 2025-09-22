#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m,k,g;
int a,b,c;

vector < pair<int,int> > graph[20005];

bool nt[23][23];

int odl[20005];
priority_queue < pair<int,int> > pq;

int grk[23][23];
int po[23],ko[23];

void dijreset()
{
    for(int i=1;i<=n;i++)
    {
        odl[i]=99999999;
    }

    while(!pq.empty()) pq.pop();
}

void dijkstra(int x,int l)
{
    if(l>odl[x]) return;
    odl[x]=l;

    for(int i=0;i<graph[x].size();i++)
    {
        pq.push({-odl[x]-graph[x][i].ss,graph[x][i].ff});
    }
}

int dp[(1<<23)];
int ost[(1<<23)];
int mask,h;

void upd(int x,int y,int num)
{
    if(y==0)
    {
        return;
    }

    if(x == ((1<<n)-1))
    {
        h=ko[num];
    }
    else h=0;

    for(int i=0;i<n;i++)
    {
        if(((y&(1<<i))>0) && nt[i][num])
        {
            cout<<"nt"<<i<<" "<<num<<"\n";
            return;
        }
    }

    if(dp[x]>dp[y]+grk[ost[y]][num]+h)
    {
        dp[x]=dp[y]+grk[ost[y]][num]+h;
        ost[x]=num;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>k;

    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        graph[a].pb({b,c});
        graph[b].pb({a,c});
    }

    cin>>g;

    for(int i=0;i<g;i++)
    {
        cin>>a>>b;
        nt[b-2][a-2]=1;
    }

    for(int i=1;i<=k+1;i++)
    {
        dijreset();
        odl[i]=0;
        pq.push({0,i});

        while(!pq.empty())
        {
            dijkstra(pq.top().ss , -pq.top().ff);
            pq.pop();
        }

        for(int j=i;j<=k+1;j++)
        {
            grk[i-2][j-2]=odl[j];
            grk[j-2][i-2]=odl[j];
        }

        if(i!=1) po[i-2]=odl[1];
        ko[i-2]=odl[n];

        //for(int j=1;j<=k+1;j++) cout<<odl[j]<<" ";
        //cout<<"\n";
    }

    /*for(int i=1;i<=k+1;i++)
    {
        for(int j=1;j<=k+1;j++) cout<<grk[i][j]<<" ";
        cout<<"\n";
    }*/

    // 1 - k+2
    n=k;

    for(int i=0;i<(1<<n);i++)
    {
        dp[i]=99999999;
    }

    for(int i=0;i<n;i++)
    {
        dp[(1<<i)] = po[i];
        ost[(1<<i)] = i;
    }

    for(int i=1;i<(1<<n);i++)
    {
        for(int nr=0;nr<n;nr++)
        {
            if(((i&(1<<nr)))>0)
            {
                mask=(i^(1<<nr));
                upd(i,mask,nr);
            }
        }
    }

    //for(int i=1;i<(1<<n);i++) cout<<i<<" "<<dp[i]<<" "<<ost[i]<<"\n";
    cout<<dp[(1<<n)-1];



    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
