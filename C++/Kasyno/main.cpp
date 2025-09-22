#include <bits/stdc++.h>
#include <ctime>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

ll n=10e18;
ll p=10e4;

ll x;
ll ile=0;

void check(ll a)
{
    for(int i=2;i<=100;i++)
    {
        while(a%i == 0) a/=i;
    }
    if(a==1) ile++;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    srand(12312);

    for(int i=1;i<=p;i++)
    {
        x=rand();
        check(x);
        cout<<RAND_MAX<<" ";
    }
    cout<<ile;


    return 0;
}
