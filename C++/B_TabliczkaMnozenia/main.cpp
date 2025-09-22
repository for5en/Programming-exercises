#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

ll m,k;
ll pq[1000010];
int l[1000010],p[1000010];
int pqsize=0;

void popraw(int id)
{
    while(id>1)
    {
        if(pq[id] > pq[id/2])
        {
            swap(pq[id],pq[id/2]);
            swap(l[id], l[id/2]);
            swap(p[id], p[id/2]);
        }
        else break;
        id/=2;
    }
}

void poprawdol(int id)
{
    while(true)
    {
        if(id*2+1 <= pqsize)
        {
            if(pq[id*2] > pq[id*2+1])
            {
                if(pq[id] < pq[id*2])
                {
                    swap(pq[id],pq[id*2]);
                    swap(l[id], l[id*2]);
                    swap(p[id], p[id*2]);
                    id=id*2;
                }
                else if(pq[id] < pq[id*2+1])
                {
                    swap(pq[id],pq[id*2+1]);
                    swap(l[id], l[id*2+1]);
                    swap(p[id], p[id*2+1]);
                    id=id*2+1;
                }
                else break;
            }
            else
            {
                if(pq[id] < pq[id*2+1])
                {
                    swap(pq[id],pq[id*2+1]);
                    swap(l[id], l[id*2+1]);
                    swap(p[id], p[id*2+1]);
                    id=id*2+1;
                }
                else if(pq[id] < pq[id*2])
                {
                    swap(pq[id],pq[id*2]);
                    swap(l[id], l[id*2]);
                    swap(p[id], p[id*2]);
                    id=id*2;
                }
                else break;
            }
        }
        else if(id*2 <= pqsize)
        {
            if(pq[id] < pq[id*2])
            {
                swap(pq[id],pq[id*2]);
                swap(l[id], l[id*2]);
                swap(p[id], p[id*2]);
                id=id*2;
            }
            else break;
        }
        else break;
    }
}

void addpq(ll a,ll b)
{
    //cout<<val;
    l[pqsize+1] = a;
    p[pqsize+1] = b;
    pq[pqsize+1]=a*b;
    pqsize++;
    popraw(pqsize);
}


ll getmax()
{
    if(pqsize == 0) return 0;
    ll a = l[1];
    ll b = p[1];

    if(a == b && a-1 >= 0)
    {
        addpq(a-1,b-1);
        addpq(a-1,b);
    }
    else if(a-1 >= 0)
    {
        addpq(a-1,b);
    }

    swap(pq[1],pq[pqsize]);
    swap(l[1], l[pqsize]);
    swap(p[1], p[pqsize]);

    pq[pqsize]=0;
    l[pqsize]=0;
    p[pqsize]=0;

    pqsize--;
    poprawdol(1);

    //cout<<a<<" "<<b<<" ";
    return a*b;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>m>>k;

    addpq(m, m);

    for(int i=1;i<=k;i++)
    {
        cout<<getmax()<<"\n";
        //for(int j=1;j<=pqsize;j++) cout<<pq[j]<<" ";
        //cout<<"\n";
    }



    return 0;
}
