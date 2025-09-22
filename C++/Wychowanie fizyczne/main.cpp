#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
int tab[100005];
int w,r;

bitset <100005> bs;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>tab[i];
    }

    for(int i=1;i<=n;i++)
    {
        //cout<<i<<":\n";
        for(int j=1;j<=n;j++)
        {
            if(!bs[tab[j]])
            {
                //cout<<"r "<<j<<"\n";
                r++;
                bs[tab[j]]=1;
            }
            if(r>i)
            {
                //cout<<"w "<<j<<"\n";
                r=1;
                w++;
                bs=0;
                bs[tab[j]]=1;
            }
        }
        cout<<w+1<<" ";
        bs=0;
        w=0;
        r=0;

    }


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
