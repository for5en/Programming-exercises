#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

string s;
int odp;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>s;

    for(int i=1;i<s.length();i++)
    {
        if(s[i]!=s[i-1]) odp++;
    }

    cout<<odp;

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
