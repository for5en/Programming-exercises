#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int z;
int m,t;
char a,b,c;
int ntp[8][8];
int tp[36];
int skad[1<<8][1<<8];
string w;
int n;
int dp[1005][1005];

void wylicz(int x,int y)
{
    for(int i=x;i<=y-1;i++)
    {
        dp[x][y] |= skad[dp[x][i]][dp[i+1][y]];
    }
}

void reset()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++) ntp[i][j]=0;
    }
    for(int i=0;i<36;i++) tp[i]=0;
    for(int i=0;i<=1000;i++)
    {
        for(int j=0;j<=1000;j++) dp[i][j]=0;
    }
    for(int i=0;i<(1<<8);i++)
    {
        for(int j=0;j<(1<<8);j++)
        {
            skad[i][j]=0;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>z;
    while(z--)
    {
        cin>>m>>t;
        for(int i=1;i<=m;i++)
        {
            cin>>a>>b>>c;
            ntp[b-'A'][c-'A'] |= (1<<(a-'A'));
        }
        for(int i=1;i<=t;i++)
        {
            cin>>a>>b;
            tp[b-'a'] |= (1<<(a-'A'));
        }
        cin>>w;
        n=w.length();
        for(int i=0;i<(1<<8);i++)
        {
            for(int j=0;j<(1<<8);j++)
            {
                int temp=0;
                for(int ii=0;ii<8;ii++)
                {
                    for(int jj=0;jj<8;jj++)
                    {
                        if((i & (1<<ii)) && (j & (1<<jj)))
                        {
                            //if(ntp[ii][jj]!=0) cout<<ii<<" "<<jj<<" "<<ntp[ii][jj]<<"\n";
                            temp |= ntp[ii][jj];
                        }
                    }
                }
                skad[i][j] = temp;
            }
        }

        for(int i=0;i<n;i++)
        {
            dp[i][i] = tp[w[i]-'a'];
        }
        for(int i=n-1;i>=0;i--)
        {
            for(int j=1;j<n;j++)
            {
                wylicz(i,j);
            }
        }
        /*for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<dp[i][j]<<" ";
            }
            cout<<"\n";
        }*/
        if(dp[0][n-1] & 1) cout<<"TAK\n";
        else cout<<"NIE\n";
        reset();
    }

    return 0;
}
