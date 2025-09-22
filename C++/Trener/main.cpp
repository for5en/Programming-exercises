#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,k;
string s,o,p;
unordered_map <string,ll> mapa[52];
ll h;
ll mod=1000000007;
ll odp;

string bezp(string bp)
{
    string bph="";
    for(int i=1;i<bp.size();i++)
    {
        bph+=bp[i];
    }
    return bph;
}

string bezo(string bp)
{
    bp.pop_back();
    return bp;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;

    for(int i=1;i<=k;i++)
    {
        cin>>s;
        mapa[1][s]++;
    }

    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            cin>>s;
            p=bezp(s);
            o=bezo(s);

            h=mapa[i-1][p];
            if(o!=p) h+=mapa[i-1][o];

            h%=mod;
            //cout<<h<<" ";
            mapa[i][s]+=h;
            mapa[i][s]%=mod;

            if(i==n)
            {
                odp+=h;
                odp%=mod;
            }
        }

        //cout<<"\n";
    }

    cout<<odp;


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
