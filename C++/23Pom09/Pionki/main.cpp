#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m,p,num;
int w,xp,yp,xh,yh;
int av,bv,av2,bv2;

vector <pair<pair<int,int>,int>> v[100005];
vector <pair<pair<int,int>,int>> v2[100005];

int rep[1000005];
int ile[1000005];

int Find(int a)
{
    while(a!=rep[a]) a=rep[a];
    return a;
}

void Union(int a,int b)
{
    a=Find(a);
    b=Find(b);
    if(ile[b]>ile[a]) swap(a,b);
    rep[b]=a;
}


int rep2[1000005];
int ile2[1000005];

int Find2(int a)
{
    while(a!=rep2[a]) a=rep2[a];
    return a;
}

void Union2(int a,int b)
{
    a=Find2(a);
    b=Find2(b);
    if(ile2[b]>ile2[a]) swap(a,b);
    rep2[b]=a;
}

void genfau()
{
    for(int i=1;i<=1000003;i++)
    {
        rep[i]=i;
        rep2[i]=i;
        ile[i]=1;
        ile2[i]=1;
    }
}

void pnab(int poz)
{
    int po=1;
    for(int i=0;i<v[poz].size();i++)
    {
        if(po<v[poz][i].ff.ff)
        {
            v2[poz].pb({{po,v[poz][i].ff.ff},num});
            po=v[poz][i].ff.ff+1;
            num++;
        }
    }
}

int znajdz(int poz,int x)
{
    for(int i=0;i<v[poz].size();i++)
    {
        if(v[poz][i].ff.ff<=x&&v[poz][i].ff.ss>=x)
        {
            return v[poz][i].ss;
        }
    }
    return 0;
}


int znajdz2(int poz,int x)
{
    for(int i=0;i<v2[poz].size();i++)
    {
        if(v2[poz][i].ff.ff<=x&&v2[poz][i].ff.ss>=x)
        {
            return v2[poz][i].ss;
        }
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>p;

    genfau();

    for(int i=1;i<=m;i++)
    {
        cin>>w>>xp>>yp;
        v[w].pb({{xp,yp},i});
    }
    num=1;

    //union czarnych
    sort(v[1].begin(),v[1].end());
    pnab(1);
    for(int i=2;i<=n;i++)
    {
        sort(v[i].begin(),v[i].end());
        pnab(i);
        av=0;
        bv=0;
        while(av<v[i-1].size()&&bv<v[i-1].size())
        {
            if(v[i-1][av].ff.ff<=v[i][bv].ff.ff)
            {
                if(v[i-1][av].ff.ss>=v[i][bv].ff.ff)
                {
                    Union(v[i-1][av].ss,v[i][bv].ss);
                }
            }
            else
            {
                if(v[i-1][av].ff.ff<=v[i][bv].ff.ss)
                {
                    Union(v[i-1][av].ss,v[i][bv].ss);
                }
            }

            if(v[i-1][av].ff.ss<=v[i][bv].ff.ss)
            {
                av++;
            }
            else
            {
                bv++;
            }
        }
    }


    //union bialych
    sort(v2[1].begin(),v2[1].end());
    for(int i=2;i<=n;i++)
    {
        sort(v2[i].begin(),v2[i].end());
        av2=0;
        bv2=0;
        while(av2<v2[i-1].size()&&bv2<v2[i-1].size())
        {
            if(v2[i-1][av2].ff.ff<=v2[i][bv2].ff.ff)
            {
                if(v2[i-1][av2].ff.ss>=v2[i][bv2].ff.ff)
                {
                    Union2(v2[i-1][av2].ss,v2[i][bv2].ss);
                }
            }
            else
            {
                if(v2[i-1][av2].ff.ff<=v2[i][bv2].ff.ss)
                {
                    Union2(v2[i-1][av2].ss,v2[i][bv2].ss);
                }
            }

            if(v2[i-1][av2].ff.ss<=v2[i][bv2].ff.ss)
            {
                av2++;
            }
            else
            {
                bv2++;
            }
        }
    }

    for(int i=0;i<p;i++)
    {
        cin>>xp>>yp>>xh>>yh;
        av=znajdz(xp,yp);
        if(av==0)
        {
            av=znajdz2(xp,yp);
            bv=znajdz2(xh,yh);
        }
        else
        {
            bv=znajdz(xh,yh);
        }

        if(av==bv)
        {
            cout<<"TAK\n";
        }
        else
        {
            cout<<"NIE\n";
        }
    }




    return 0;
}

