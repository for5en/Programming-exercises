#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
pair<pair<int,int>,int> h;
vector <pair<pair<int,int>,int>> v;

auto upperbound(vector <pair<pair<int,int>,int>> &a,pair<pair<int,int>,int> &b)
{
    auto up = upper_bound(a.begin(),a.end(),b);
    return (up-a.begin());
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=0;i<=10;i++)
    {
        h={{pow(2,i),0},0};
        v.pb(h);
    }

    h={{n,0},0};
    auto it=upperbound(v,h);

    cout<<(*it).ss;

    return 0;
}
