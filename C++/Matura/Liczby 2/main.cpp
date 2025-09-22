#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,a;
int tabs[15];
bool czy;

int sc(int x)
{
    int s=0;

    while(x>0)
    {
        s+=tabs[x%10];
        x/=10;
    }

    return s;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    czy=1;
    tabs[0]=1;
    tabs[1]=1;
    for(int i=2;i<=9;i++) tabs[i]=tabs[i-1]*i;

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(a==sc(a))
        {
            cout<<a<<"\n";
            czy=0;
        }
    }
    if(czy) cout<<"brak";

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
