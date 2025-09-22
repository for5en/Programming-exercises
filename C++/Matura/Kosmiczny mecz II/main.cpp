#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

string s;
int p,a,b;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>s>>p;

    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='A') a++;
        else b++;

        if(a>=p&&a>=b+3)
        {
            cout<<"A\n"<<a<<":"<<b;
            return 0;
        }
        else if(b>=p&&b>=a+3)
        {
            cout<<"B\n"<<a<<":"<<b;
            return 0;
        }
    }


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
