#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
int a,b;

vector <pair<int,int>> g;
int po[500005];
int s,odp1;
vector <int> godp;

int s1,s2,odp2,s1h,s2h;
bool czy1,czy2;
vector <pair<int,int>> hodp;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;
        po[i]=a;
        g.pb({b,i});
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
            a=g[i].ss;
            czy1=1;
        }
        else if(!czy2&&s1<=po[g[i].ss])
        {
            s2h=g[i].ff;
            b=g[i].ss;
            czy2=1;
        }

        if(czy1&&czy2)
        {
            s1=s1h;
            s2=s2h;
            odp2++;
            hodp.pb({a,b});
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

    /*cout<<odp1-1<<"\n";
    for(int i=1;i<godp.size();i++)
    {
        cout<<godp[i]<<" "<<godp[0]<<"\n";
    }*/


    return 0;
}
