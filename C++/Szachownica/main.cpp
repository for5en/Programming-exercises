#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,p,m;

int mask;
int wzorce[105];

vector <int> skad[1<<5];

int dp[2][1<<10];

void zeruj(int x)
{
    for(int i=0; i<(1<<10); i++)
    {
        dp[x][i] = 0;
    }
}

bool jest(int x, int y)
{
    for(int i=1; i<=p ;i++)
    {
        if(((y>>7)<<6) + (((y%(1<<5))>>2)<<3) + (x>>2) == wzorce[i]) return 1;
        if((((y%(1<<9))>>6)<<6) + (((y%(1<<4))>>1)<<3) + ((x%(1<<4))>>1) == wzorce[i]) return 1;
        if((((y%(1<<8))>>5)<<6) + ((y%(1<<3))<<3) + (x%(1<<3)) == wzorce[i]) return 1;
    }

    return 0;
}

void pokaz(int x)
{
    for(int i=0; i<=2; i++)
    {
        for(int j=0; j<=4; j++)
        {
            if(x >= 1<<(14 - i*5 - j))
            {
                cout << 'x';
                x -= 1<<(14 - i*5 - j);
            }
            else cout << '.';
        }
        cout << "\n";
    }
    cout<<"\n";
}

int wezk()
{
    char c;
    int odp = 0;

    cin >> c;
    if(c == 'x') odp += (1<<6);

    cin >> c;
    if(c == 'x') odp += (1<<3);

    cin >> c;
    if(c == 'x') odp += (1<<0);

    cin >> c;
    if(c == 'x') odp += (1<<7);

    cin >> c;
    if(c == 'x') odp += (1<<4);

    cin >> c;
    if(c == 'x') odp += (1<<1);

    cin >> c;
    if(c == 'x') odp += (1<<8);

    cin >> c;
    if(c == 'x') odp += (1<<5);

    cin >> c;
    if(c == 'x') odp += (1<<2);

    return odp;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> p >> m;

    for(int i=1; i<=p; i++)
    {
        mask = wezk();
        wzorce[i] = mask;
    }

    for(int i=0; i<(1<<5); i++)
    {
        for(int j=0; j<(1<<10); j++)
        {
            if(!jest(i,j))
            {
                //cout<<i<<" "<<j<<":\n";
                //pokaz((j<<5) + i);
                skad[i].pb(j);
            }
        }
    }

    ////////////////////////////////////////////////////

    for(int i=0; i<(1<<10); i++) dp[0][i] = 1;

    for(int i=3; i<=n; i++)
    {
        // liczymy dp[i%2]
        zeruj(i%2);
        for(int j=0; j<(1<<5); j++)
        {
            for(int k=0; k<skad[j].size(); k++)
            {
                //pokaz((skad[j][k]<<5) + j);
                dp[i%2][((skad[j][k]%(1<<5))<<5) + j] = (dp[i%2][((skad[j][k]%(1<<5))<<5) + j] + dp[(i+1)%2][skad[j][k]]) % m;
            }
        }
    }

    int sum = 0;

    for(int i=0; i<(1<<10); i++)
    {
        sum += dp[n%2][i];
        sum %= m;
        //cout << i<<" "<<dp[n%2][i]<<"\n";
    }

    cout<<sum;

    return 0;
}
