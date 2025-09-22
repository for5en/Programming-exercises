#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,l,m;
int a,b,p1,p2;
string s[1005];
int odp[1005];

unordered_map <string,int> mapa;

void start()
{
    for(int i=1;i<=n;i++)
    {
        odp[i]=mapa[s[i]];
    }
}

void update(string str)
{
    //cout<<str<<":\n";
    int h=mapa[str];
    for(int i=1;i<=n;i++)
    {
        if(s[i]==str)
        {
            odp[i]=max(odp[i],h);
            //cout<<i<<" "<<odp[i]<<"\n";
        }

    }
}

void zmiana(int px,int x,int py,int y)
{
    x--;
    y--;

    mapa[s[px]]--;
    if(px!=py) mapa[s[py]]--;

    char t1=s[px][x];
    char t2=s[py][y];

    s[px][x]=t2;
    s[py][y]=t1;

    mapa[s[px]]++;
    if(px!=py) mapa[s[py]]++;

    update(s[px]);
    if(px!=py) update(s[py]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>l>>m;

    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
        mapa[s[i]]++;
    }

    start();

    for(int i=1;i<=m;i++)
    {
        cin>>p1>>a>>p2>>b;
        zmiana(p1,a,p2,b);
    }

    for(int i=1;i<=n;i++) cout<<odp[i]<<"\n";



    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
