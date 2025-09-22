#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
int tab[100005];

int an,adl,as;
int pn,pdl,ps;
// nwd, dlugosc, poczatek


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
        an=tab[i];
        as=tab[i];
        adl=1;
        for(int j=i+1;j<=n;j++)
        {
            if(__gcd(an,tab[j])>1)
            {
                an=__gcd(an,tab[j]);
                adl++;
            }
            else
            {
                break;
            }
        }

        if(adl>pdl)
        {
            pdl=adl;
            pn=an;
            ps=as;
        }
    }

    cout<<ps<<" "<<pdl<<" "<<pn;

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
