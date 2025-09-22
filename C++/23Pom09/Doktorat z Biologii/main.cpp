#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
long long p;
vector <pair<long long,int>> v;

int tab[1000005];
int dp[1000005];
vector <int> odp;

int base=1<<20;
int tree[1<<21];

void ins(int gdzie,int x)
{
    gdzie=gdzie+base-1;
    tree[gdzie]=x;
    gdzie/=2;

    while(gdzie>0)
    {
        tree[gdzie]=max(tree[gdzie*2],tree[gdzie*2+1]);
        gdzie/=2;
    }
}

int query(int gdzie,int p,int k,int a,int b)
{
    if(a<=p&&k<=b)
    {
        return tree[gdzie];
    }

    int sr=(p+k)/2;
    int mx=0;

    if(a<=sr) mx=query(gdzie*2,p,sr,a,b);
    if(sr<b) mx=max(mx,query(gdzie*2+1,sr+1,k,a,b));

    return mx;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>p;
        v.pb({p,i});
    }

    sort(v.begin(),v.end());

    int num=1;
    tab[v[0].ss]=num;
    for(int i=1;i<v.size();i++)
    {
        if(v[i-1].ff==v[i].ff)
        {
            tab[v[i].ss]=num;
        }
        else
        {
            num++;
            tab[v[i].ss]=num;
        }
    }

    int xx=0;

    for(int i=1;i<=n;i++)
    {
        //cout<<tab[i]<<" "<<n<<"\n";
        dp[i]=query(1,1,base,tab[i],n)+1;
        //cout<<query(1,1,base,tab[i],n)+1<<"\n";
        ins(tab[i],dp[i]);
        xx=max(xx,dp[i]);
    }

    cout<<xx<<"\n";

    for(int i=n;i>=1;i--)
    {
        if(dp[i]==xx)
        {
            odp.pb(i);
            xx--;
        }
    }

    for(int i=odp.size()-1;i>=0;i--)
    {
        cout<<odp[i]<<" ";
    }





    return 0;
}
