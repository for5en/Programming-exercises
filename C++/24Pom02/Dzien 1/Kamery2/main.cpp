#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

ll inf=1e9;
ll n,odp;
ll a,b;
ll stan[100005];
vector <ll> graph[100005];

ll dp[100005][2][2];

ll oblicz(ll y,ll p,bool kol,bool par)
{
    ll mnr=inf;
    ll czm=0;
    ll suma=0;

    for(ll i=0;i<graph[y].size();i++)
    {
        if(graph[y][i]!=p)
        {
            if(dp[graph[y][i]][kol][0]<dp[graph[y][i]][kol][1])
            {
                suma+=dp[graph[y][i]][kol][0];
                mnr=min(mnr,dp[graph[y][i]][kol][1]-dp[graph[y][i]][kol][0]);
            }
            else
            {
                suma+=dp[graph[y][i]][kol][1];
                czm++;
                mnr=min(mnr,dp[graph[y][i]][kol][0]-dp[graph[y][i]][kol][1]);
            }
        }
    }

    if(par==0)
    {
        if(czm%2==1) suma+=mnr;
    }
    else
    {
        if(czm%2==0) suma+=mnr;
    }

    //cout<<y<<" "<<czm<<" "<<mnr<<"\n";

    return suma;
}

void dfs(ll x,ll r)
{
    ll czm=0;
    for(ll i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=r)
        {
            dfs(graph[x][i],x);
        }
    }
    // wyliczanie dpka

    if(graph[x].size()>1||x==1)
    {
        dp[x][0][0]=oblicz(x,r,0,stan[x]);
        dp[x][0][1]=oblicz(x,r,1,!stan[x])+1;
        dp[x][1][0]=oblicz(x,r,0,!stan[x]);
        dp[x][1][1]=oblicz(x,r,1,stan[x])+1;
    }
    else
    {
        dp[x][stan[x]][0]=0;
        dp[x][stan[x]][1]=inf;
        dp[x][!stan[x]][0]=inf;
        dp[x][!stan[x]][1]=1;
    }
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(ll i=1;i<n;i++)
    {
        cin>>a>>b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    for(ll i=1;i<=n;i++) cin>>stan[i];

    dfs(1,0);

    /*for(ll i=1;i<=n;i++)
    {
        cout<<i<<":  cx"<<dp[i][0][0]<<" cv"<<dp[i][0][1]<<" bx"<<dp[i][1][0]<<" bv"<<dp[i][1][1]<<"\n";
    }*/

    odp=min(dp[1][0][0],dp[1][0][1]);
    if(odp>=inf) cout<<"impossible";
    else cout<<odp;


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
