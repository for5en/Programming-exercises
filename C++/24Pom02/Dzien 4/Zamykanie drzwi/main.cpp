#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m;
int a,b;
vector <int> graph[100005];
int wej[100005];
bitset <100005> odw;
pair <int,int> kra[100005];
int odp;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        graph[a].pb(b);
        kra[i]={a,b};g
    }

    for(int i=1;i<=m;i++)
    {
        odp+=(graph[kra[i].ff].size()-1);
    }

    cout<<odp;



    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
