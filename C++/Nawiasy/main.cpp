#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

ll mod=1e9;
int n;
char c[5005];
ll dp[5005];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    n--;
    for(int i=1;i<=n;i++)
    {
        cin>>c[i];
        dp[i]=1;
    }

    for(int i=2;i<=n;i++)
    {
        if(c[i]=='-'&&c[i-1]=='+')
        {
            for(int j=i;j<=n;j++)
            {
                dp[j]+=dp[j-1];
                dp[j]%=mod;
            }
        }
    }

    if(c[1]=='+') cout<<"0";
    else cout<<dp[n];


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
