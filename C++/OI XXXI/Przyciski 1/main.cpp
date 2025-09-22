#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m,c,r;

int tr[500010], tc[500010];
vector <pair<int,int>> rows[100010], cols[100010];
vector <int> graph[500010];

bool czy=1;
bitset <500010> odw;
vector <int> cykl,ostcykl;

vector <pair<int,int>> gpr[200010];
bitset <200010> dz;
bitset <500010> nieb;
int ilenie;
// 0 - zly (parzyscie wierzcholkow), 1 - dobry (nieparzyscie wierzcholkow)
int pcykl;

bool dfscykl(int x,int p)
{
    //cout<<x<<"\n";
    odw[x]=1;
    for(int i=0;i<graph[x].size();i++)
    {
        if(!odw[graph[x][i]]&&czy)
        {
            if(dfscykl(graph[x][i],x))
            {
                cykl.pb(x);
                if(x==pcykl) return 0;
                return 1;
            }
        }
        else if(graph[x][i]!=p&&czy)
        {
            pcykl=graph[x][i];
            czy=0;
            //cout<<x<<"pcykl"<<pcykl<<"\n";
            cykl.pb(x);
            return 1;
        }
    }

    return 0;
}

bool dfstree(int x)
{
    odw[x]=1;
    int suma=0,h=0;

    /*cout<<x<<" "<<gpr[x].size()<<"\n";

    if(gpr[x].size()==0)
    {
        czy=0;
        return 0;
    }*/

    if(dz[x]) // dobra prosta
    {
        for(int i=0;i<gpr[x].size();i++)
        {
            if(!odw[gpr[x][i].ff])
            {
                h=dfstree(gpr[x][i].ff);
                suma+=h;
                if(h==0)
                {
                    //cout<<gpr[x][i].ss<<"n\n";
                    nieb[gpr[x][i].ss]=1;
                    ilenie++;
                }
            }
        }
        if(suma==0) return 0;
        if(suma==1) return 1;
        if(suma==2) return 0;
        czy=0;
        return 0;
    }
    else // zla prosta
    {
        for(int i=0;i<gpr[x].size();i++)
        {
            if(!odw[gpr[x][i].ff])
            {
                h=dfstree(gpr[x][i].ff);
                suma+=h;
                if(h==0)
                {
                    //cout<<gpr[x][i].ss<<"n\n";
                    nieb[gpr[x][i].ss]=1;
                    ilenie++;
                }
            }
        }
        if(suma==0) return 1;
        if(suma==1) return 0;
        czy=0;
        return 0;
    }

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=m;i++)
    {
        cin>>r>>c;
        tr[i]=r;
        tc[i]=c;
        rows[r].pb({c,i});
        cols[c].pb({r,i});
        gpr[r].pb({c+100000,i});
        gpr[c+100000].pb({r,i});
        dz[r]=!dz[r];
        dz[c+100000]=!dz[c+100000];
    }

    // dla parzystego modulo

    // tworzenie grafu
    for(int i=1;i<=n;i++)
    {
        sort(rows[i].begin(),rows[i].end());
        sort(cols[i].begin(),cols[i].end());
    }

    for(int i=1;i<=n;i++)
    {
        if(rows[i].size()>0)
        {
            for(int j=0;j<rows[i].size()-1;j++)
            {
                graph[rows[i][j].ss].pb(rows[i][j+1].ss);
                graph[rows[i][j+1].ss].pb(rows[i][j].ss);
            }
        }
        if(cols[i].size()>0)
        {
            for(int j=0;j<cols[i].size()-1;j++)
            {
                graph[cols[i][j].ss].pb(cols[i][j+1].ss);
                graph[cols[i][j+1].ss].pb(cols[i][j].ss);
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(!odw[i]&&czy)
        {
            dfscykl(i,0);
        }
    }

    // wywalanie wspolliniowych i wypisywanie odpowiedzi

    if(cykl.size()>=4)
    {
        // modulo = 2
        if(tr[cykl[1]]!=tr[cykl[cykl.size()-1]] && tc[cykl[1]]!=tc[cykl[cykl.size()-1]]) ostcykl.pb(cykl[0]);
        if(tr[cykl[0]]!=tr[cykl[cykl.size()-2]] && tc[cykl[0]]!=tc[cykl[cykl.size()-2]]) ostcykl.pb(cykl[cykl.size()-1]);
        for(int i=1;i<cykl.size()-1;i++)
        {
            if(tr[cykl[i-1]]!=tr[cykl[i+1]] && tc[cykl[i-1]]!=tc[cykl[i+1]]) ostcykl.pb(cykl[i]);
        }
        /*for(int i=0;i<cykl.size();i++)
        {
            ostcykl.pb(cykl[i]);
        }*/


        sort(ostcykl.begin(),ostcykl.end());
        cout<<"TAK\n"<<ostcykl.size()<<"\n";
        for(int i=0;i<ostcykl.size();i++)
        {
            cout<<ostcykl[i]<<" ";
        }
        return 0;
    }
    else
    {
        // modulo = 1 - graf acykliczny nieskierowany
        for(int i=1;i<=200000;i++)
        {
            odw[i]=0;
        }

        for(int i=1;i<=n;i++)
        {
            czy=1;
            //cout<<dz[i]<<"\n";
            if(!odw[i]&&!dz[i])
            {
                //cout<<i<<"i\n";
                if(dfstree(i)==0)
                {
                    if(czy==0)
                    {
                        cout<<"NIE\n";
                        return 0;
                    }
                }
                else
                {
                    cout<<"NIE\n";
                    return 0;
                }
            }
        }

        for(int i=100001;i<=n+100000;i++)
        {
            czy=1;
            //cout<<dz[i]<<"\n";
            if(!odw[i]&&!dz[i])
            {
                //cout<<i<<"i\n";
                if(dfstree(i)==0)
                {
                    if(czy==0)
                    {
                        cout<<"NIE\n";
                        return 0;
                    }
                }
                else
                {
                    cout<<"NIE\n";
                    return 0;
                }
            }
        }

        /*for(int i=1;i<=n;i++)
        {
            if(!odw[i]&&!dz[i])
            {
                cout<<"NIE\n";
                return 0;
            }
            if(!odw[i+100000]&&!dz[i+100000])
            {
                cout<<"NIE\n";
                return 0;
            }
        }*/

        for(int i=1;i<=m;i++)
        {
            if(!odw[tr[i]]&&!odw[tc[i]+100000]&&dz[tr[i]]&&dz[tc[i]+100000])
            {
                nieb[i]=1;
                ilenie++;
            }
        }
    }

    cout<<"TAK\n"<<ilenie<<"\n";
    for(int i=1;i<=m;i++)
    {
        if(nieb[i]) cout<<i<<" ";
    }

    /*for(int i=1;i<=m;i++)
    {
        cout<<i<<":\n";
        for(int j=0;j<graph[i].size();j++)
        {
            cout<<graph[i][j]<<" ";
        }
        cout<<"\n";
    }*/


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
