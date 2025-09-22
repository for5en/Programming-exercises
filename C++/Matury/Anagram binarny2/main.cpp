#include <bits/stdc++.h>
#include <fstream>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

fstream plik;
int n=1000;
string s[1005];
vector <string> v;
int mx;
bool cyf[1005][15];

int zero;
int mxsum,licb;

int strtodec(string str)
{
    int odp=0;
    int h=1;

    for(int i=str.size()-1;i>=0;i--)
    {
        if(str[i]=='1') odp+=h;
        h*=2;
    }
    return odp;
}

int ab(int x,int id)
{
    while(x>0)
    {
        cyf[id][x%10]=1;
        x/=10;
    }
    if(cyf[id][0]) zero++;

    int h=0;
    for(int i=0;i<=9;i++)
    {
        if(cyf[id][i]) h+=i;
    }
    if(h>mxsum)
    {
        mxsum=h;
        licb=id;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    plik.open("anagram.txt");

    for(int i=1;i<=n;i++)
    {
        plik>>s[i];
        ab(strtodec(s[i]),i);
    }

    for(int i=1;i<n;i++)
    {
        mx=max(mx,abs(strtodec(s[i])-strtodec(s[i+1])));
    }
    cout<<mx<<"\n";

    cout<<zero<<" "<<strtodec(s[licb])<<"\n";




    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
