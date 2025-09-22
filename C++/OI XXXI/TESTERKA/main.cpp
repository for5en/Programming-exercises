#include <bits/stdc++.h>
#include <fstream>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
int a[500005],b[500005];
fstream plik;

void kodzik()
{
    vector <pair<int,int>> g;
    int po[500005];
    int s,odp1;
    vector <int> godp;

    int s1,s2,odp2,s1h,s2h,x,y;
    bool czy1,czy2;
    vector <pair<int,int>> hodp;

    godp.clear();
    hodp.clear();

    s=0;
    odp1=0;
    odp2=0;
    s1=0;
    s2=0;
    s1h=0;
    s2h=0;
    czy1=0;
    czy2=0;
    x=0;
    y=0;
    fill(po,po+500002,0);

    for(int i=1;i<=n;i++)
    {
        po[i]=a[i];
        g.pb({b[i],i});
    }

    sort(g.begin(),g.end());

    // L-1

    for(int i=0;i<g.size();i++)
    {
        if(po[g[i].ss]>=s)
        {
            odp1++;
            godp.pb(g[i].ss);
            s=g[i].ff;
        }
    }

    // L

    for(int i=0;i<g.size();i++)
    {
        if(!czy1&&s2<=po[g[i].ss]&&s1<=po[g[i].ss])
        {
            s1h=g[i].ff;
            x=g[i].ss;
            czy1=1;
        }
        else if(!czy2&&s1<=po[g[i].ss])
        {
            s2h=g[i].ff;
            y=g[i].ss;
            czy2=1;
        }

        if(czy1&&czy2)
        {
            s1=s1h;
            s2=s2h;
            odp2++;
            hodp.pb({x,y});
            czy1=0;
            czy2=0;
        }
    }

    if(odp1-1>=odp2)
    {
        cout<<odp1-1<<"\n";
        for(int i=1;i<godp.size();i++)
        {
            cout<<godp[i]<<" "<<godp[0]<<"\n";
        }
    }
    else
    {
        cout<<odp2<<"\n";
        for(int i=0;i<hodp.size();i++)
        {
            cout<<hodp[i].ff<<" "<<hodp[i].ss<<"\n";
        }
    }
}

void odczytin(string s,int x)
{
    plik.open( s+to_string(x), std::ios::in | std::ios::out );
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    plik.open( "nazwa_pliku.txt", std::ios::in | std::ios::out );


    return 0;
}
