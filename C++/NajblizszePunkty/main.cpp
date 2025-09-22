#include <bits/stdc++.h>
//#include <fstream>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
int a,b;
pair<ll,ll> tab[1000005];

ll dst(int x,int y)
{
    return (tab[x].ff-tab[y].ff)*(tab[x].ff-tab[y].ff)+(tab[x].ss-tab[y].ss)*(tab[x].ss-tab[y].ss);
}

int dstx(int x,int m)
{
    return abs(tab[x].ff-m);
}

int dsty(int x,int y)
{
    return abs(tab[x].ss-tab[y].ss);
}

pair<int,int> fnd(int m, int p, ll d, ll dd,vector<pair<int,int>> taby)
{
    int iak=0;
    int jak=0;
    ll ak = dd;
    vector <pair<int,int>> v;
    for(int i=0;i<taby.size();i++)
    {
        //cout<<i<<"\n";
        if(dstx(taby[i].ss,p) < d) v.pb({taby[i].ff,taby[i].ss});
    }


    for(int i=0;i<v.size();i++)
    {
        for(int j=i+1;j<v.size()&&j<=i+10;j++)
        {
            if(dst(v[i].ss,v[j].ss) < ak)
            {
                ak = dst(v[i].ss,v[j].ss);
                iak = v[i].ss;
                jak = v[j].ss;
            }
        }
    }
    return {iak,jak};
}

pair<int,int> zap(int p,int k, vector<pair<int,int>> taby)
{
    // przypadki bazowe gdzie mamy <= 3 punkty
    if(k-p+1 == 2) return {p,k};
    if(k-p+1 == 3)
    {
        if(dst(p,p+1) < dst(p,p+2) && dst(p,p+1) < dst(p+1,p+2)) return {p,p+1};
        if(dst(p,p+2) < dst(p,p+1) && dst(p,p+2) < dst(p+1,p+2)) return {p,p+2};
        return {p+1,p+2};
    }

    int sr=(p+k)/2;

    vector<pair<int,int>> l,r;
    l.clear();
    r.clear();

    for(int i=0;i<taby.size();i++)
    {
        if(taby[i].ss<=sr) l.pb(taby[i]);
        else r.pb(taby[i]);
    }

    pair<int,int> p1 = zap(p,sr,l);
    pair<int,int> p2 = zap(sr+1,k,r);
    ll dd = min(dst(p1.ff,p1.ss), dst(p2.ff,p2.ss));
    ll d = sqrt(dd)+1;
    int pivot = tab[sr].ff;
    pair<int,int> p3 = fnd(sr,pivot,d,dd,taby);
    /*cout<<p1.ff<<" "<<p1.ss<<"\n";
    cout<<p2.ff<<" "<<p2.ss<<"\n";
    cout<<p3.ff<<" "<<p3.ss<<"\n\n";*/
    if(p3.ff == 0)
    {
        if(dst(p1.ff,p1.ss)<dst(p2.ff,p2.ss)) return p1;
        else return p2;
    }
    else
    {
        if(dst(p1.ff,p1.ss)<dst(p2.ff,p2.ss) && dst(p1.ff,p1.ss)<dst(p3.ff,p3.ss)) return p1;
        else if(dst(p2.ff,p2.ss)<dst(p1.ff,p1.ss) && dst(p2.ff,p2.ss)<dst(p3.ff,p3.ss)) return p2;
        else return p3;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    //fstream plik;
    //plik.open("pkt.txt");
    vector <pair<int,int>> taby;

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;
        tab[i]={a,b};
        taby.pb({b,i});
    }

    sort(tab+1,tab+n+1);
    sort(taby.begin(),taby.end());
    //cout<<tab[n].ff<<"\n";

    pair<int,int> odp = zap(1,n,taby);
    cout<<tab[odp.ff].ff<<" "<<tab[odp.ff].ss<<"\n";
    cout<<tab[odp.ss].ff<<" "<<tab[odp.ss].ss<<"\n";
    //cout<<dst(odp.ff,odp.ss)<<"\n\n";

    /*ll ak=1000000000000000000;
    int aki=1;
    int akj=2;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(dst(i,j) < ak)
            {
                ak=dst(i,j);
                aki=i;
                akj=j;
            }
        }
    }
    odp={aki,akj};
    cout<<tab[odp.ff].ff<<" "<<tab[odp.ff].ss<<"\n";
    cout<<tab[odp.ss].ff<<" "<<tab[odp.ss].ss<<"\n";
    cout<<dst(odp.ff,odp.ss)<<"\n\n";*/


    return 0;
}
