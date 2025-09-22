#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,q;
int a,b;
vector <int> graph[500005];
int pod[500005];
int c1,c2;

int m;
char z,zh;

int odl1[500005], odl2[500005];

int base=1<<19;
int tree1[1<<20], tree2[1<<20];
int odp;
bitset <500005> wsp,wspb;


void dfs(int x,int p)
{
    bool ctr=1;
    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=p)
        {
            dfs(graph[x][i],x);
            pod[x]+=pod[graph[x][i]];
            if(pod[graph[x][i]]>n/2) ctr=0;
        }
    }
    pod[x]++;
    if(n-pod[x]>n/2) ctr=0;

    if(ctr)
    {
        c2=c1;
        c1=x;
    }
}

void odfs1(int x,int p)
{
    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=p)
        {
            odl1[graph[x][i]]=odl1[x]+1;
            odfs1(graph[x][i],x);
        }
    }
}

void odfs2(int x,int p)
{
    for(int i=0;i<graph[x].size();i++)
    {
        if(graph[x][i]!=p)
        {
            odl2[graph[x][i]]=odl2[x]+1;
            odfs2(graph[x][i],x);
        }
    }
}

void update1(int gdzie,int ile)
{
    gdzie+=base;
    gdzie--;

    tree1[gdzie]+=ile;
    gdzie/=2;

    while(gdzie>0)
    {
        tree1[gdzie]=tree1[gdzie*2]+tree1[gdzie*2+1];
        gdzie/=2;
    }
}

void update2(int gdzie,int ile)
{
    gdzie+=base;
    gdzie--;

    tree2[gdzie]+=ile;
    gdzie/=2;

    while(gdzie>0)
    {
        tree2[gdzie]=tree2[gdzie*2]+tree2[gdzie*2+1];
        gdzie/=2;
    }
}

int query1(int gdzie,int p,int k,int x,int y)
{
    if(p<=x&&k<=y) return tree1[gdzie];

    int sr=(p+k)/2;
    int sum=0;

    if(x<=sr) sum+=query1(gdzie*2,p,sr,x,y);
    if(sr<y) sum+=query1(gdzie*2+1,sr+1,k,x,y);

    return sum;
}

int query2(int gdzie,int p,int k,int x,int y)
{
    if(p<=x&&k<=y) return tree2[gdzie];

    int sr=(p+k)/2;
    int sum=0;

    if(x<=sr) sum+=query2(gdzie*2,p,sr,x,y);
    if(sr<y) sum+=query2(gdzie*2+1,sr+1,k,x,y);

    return sum;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<n;i++)
    {
        cin>>a>>b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    dfs(1,1);

    if(c2==0) // jeden centroid
    {
        odfs1(c1,c1);

        cin>>n>>m>>q;
        for(int i=1;i<=n;i++)
        {
            cin>>a;
            wsp[a]=1;
            update1(odl1[a],1);
        }
        for(int i=1;i<=m;i++)
        {
            cin>>b;
            if(wsp[b])
            {
                odp--;
                wspb[b]=1;
            }
            odp-=query1(1,1,base,1,odl1[b]);
            odp+=(n+1);
        }
        cout<<odp<<"\n";
        for(int i=1;i<=q;i++)
        {
            cin>>zh>>z>>b;
            if(z=='+')
            {
                if(wsp[b])
                {
                    odp--;
                    wspb[b]=1;
                }
                odp-=query1(1,1,base,1,odl1[b]);
                odp+=(n+1);
            }
            else
            {
                if(wspb[b])
                {
                    odp++;
                    wspb[b]=0;
                }
                odp+=query1(1,1,base,1,odl1[b]);
                odp-=(n+1);
            }
            cout<<odp<<"\n";
        }
    }
    else // dwa centroidy
    {
        odfs1(c1,c1);
        odfs2(c2,c2);

        cin>>n>>m>>q;
        for(int i=1;i<=n;i++)
        {
            cin>>a;
            wsp[a]=1;
            update1(odl1[a],1);
            update2(odl2[a],1);
        }
        for(int i=1;i<=m;i++)
        {
            cin>>b;
            if(wsp[b])
            {
                odp--;
                wspb[b]=1;
            }
            odp-=max(query1(1,1,base,1,odl1[b]),query2(1,1,base,1,odl2[b]));
            odp+=(n+1);
        }
        cout<<odp<<"\n";
        for(int i=1;i<=q;i++)
        {
            cin>>zh>>z>>b;
            if(z=='+')
            {
                if(wsp[b])
                {
                    odp--;
                    wspb[b]=1;
                }
                odp-=max(query1(1,1,base,1,odl1[b]),query2(1,1,base,1,odl2[b]));
                odp+=(n+1);
            }
            else
            {
                if(wspb[b])
                {
                    odp++;
                    wspb[b]=0;
                }
                odp+=max(query1(1,1,base,1,odl1[b]),query2(1,1,base,1,odl2[b]));
                odp-=(n+1);
            }
            cout<<odp<<"\n";
        }
    }



    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
