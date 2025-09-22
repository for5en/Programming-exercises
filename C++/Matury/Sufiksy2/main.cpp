#include <bits/stdc++.h>
#include <fstream>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,k1,k2;
string s;
int tab[1000];
fstream plik,plik2;

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

void glowna()
{
    plik>>n>>s;
    for(int i=1;i<=n;i++) tab[i]=i;
    //cout<<s;
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            if(!czy_mniejszy(n,s,tab[i],tab[j]))
            {
                //cout<<"wtf\n";
                swap(tab[i],tab[j]);
            }
        }
    }
    //cout<<tab[1]<<" "<<n;
    for(int i=tab[1];i<=n;i++)
    {
        plik2<<s[i-1];
    }
    plik2<<"\n";
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);*/

    plik.open("slowa4.txt.");
    plik2.open("wyniki2_4.txt");

    for(int i=1;i<=10;i++)
    {
        glowna();
    }

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
