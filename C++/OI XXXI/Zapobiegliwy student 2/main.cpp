#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
int a,b;
vector <pair<pair<int,int>,int> v;
//.ff.ff - czas
//.ff.ss - typ
//.ss - numer

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;
        v.pb({{a,1},i});
        v.pb({{b,0})
    }


    return 0;
}
