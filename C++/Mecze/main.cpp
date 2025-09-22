#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,m,a;
string tab[40010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n/2;j++)
        {
            cin>>a;
            tab[a]+="0";
        }

        for(int j=1;j<=n/2;j++)
        {
            cin>>a;
            tab[a]+="1";
        }
    }

    sort(tab+1,tab+n+1);

    for(int i=1;i<=n;i++)
    {
        if(tab[i]==tab[i-1])
        {
            cout<<"NIE\n";
            return 0;
        }
    }

    cout<<"TAK\n";

    return 0;
}
