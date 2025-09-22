#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,k1,k2;
string s;

bool czy_mniejszy(int l, string str, int x,int y)
{
    int i=x;
    int j=y;
    i--;
    j--;
    l--;

    while(i<=l && j<=l)
    {
        if(str[i]==str[j])
        {
            i++;
            j++;
        }
        else
        {
            if(str[i]<str[j]) return 1;
            else return 0;
        }
    }
    if(j<=l) return 1;
    else return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>s>>k1>>k2;
    cout<<czy_mniejszy(n,s,k1,k2);

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
