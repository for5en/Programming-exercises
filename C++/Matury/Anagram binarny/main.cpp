#include <bits/stdc++.h>
#include <fstream>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

fstream plik,plik2;
int n=1000;
int z,d;
int zr,pzr;
int l;
string s;
vector <string> v;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    plik.open("anagram.txt");
    plik2.open("wyniki3.txt");

    for(int i=1;i<=n;i++)
    {
        plik>>s;
        for(int j=0;j<s.size();j++)
        {
            if(s[j]=='0') z++;
            else d++;
        }
        if(z==d) zr++;
        if(z+1==d||z-1==d) pzr++;

        if(s.size()==8&&(z==d||z+1==d-1)&&s[0]!='0') v.pb(s);
        z=0;
        d=0;
    }

    cout<<zr<<" "<<pzr<<"\n";
    for(int i=0;i<v.size();i++) plik2<<v[i]<<"\n";




    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
