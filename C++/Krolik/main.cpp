#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m;
char tab[410][410];
int dp[410][410],dpp[410][410];

void opuscdp()
{
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dpp[i][j]=dp[i][j];
            dp[i][j]=0;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>tab[i][j];
        }
    }

    if(tab[1][1]==tab[n][m])
    {
        dp[1][1]=1;
        dp[n][m]=1;
    }
    else
    {
        cout<<"0";
        return 0;
    }

    opuscdp();
    int k=2;






    return 0;
}
