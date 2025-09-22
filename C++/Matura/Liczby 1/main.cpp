#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,a,odp;
bitset <100005> czy;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for(int i=1;i<=100000;i*=3)
    {
        czy[i]=1;
    }

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(czy[a]) odp++;
    }

    cout<<odp;


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
