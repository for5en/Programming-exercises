#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m,a;
int mx,mn;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    mn=999;

    cin>>n>>m;

    for(int i=1;i<=n*m;i++)
    {
        cin>>a;
        mn=min(mn,a);
        mx=max(mx,a);
    }

    cout<<mn<<" "<<mx;



    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
