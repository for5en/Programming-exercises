#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

string s;
int p;

int a;

int np;
char d;

int odp;
// liczba pass

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);*/

    cin>>s>>p;

    a=1;
    for(int i=1;i<s.length();i++)
    {
        if(s[i]==s[i-1]) a++;
        else
        {
            if(a>=p) odp++;
            if(np<a)
            {
                np=a;
                d=s[i-1];
            }
            a=1;
        }
    }

    if(a>p) odp++;
    if(np<a)
    {
        np=a;
        d=s[s.length()-1];
    }

    cout<<odp<<"\n";
    cout<<np<<":"<<d;


    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
