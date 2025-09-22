#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,k;
ll a,b;
string s,ps;

int ile[2000000][27];
char mxlit[2000000];

string sk;
char litk;

string cykl;

unordered_map <string,int> mapa;
// klucz-string, numer-int
int num;

int Z[2000010];

ll cmin(ll xa, ll xb)
{
    if(xa>xb) return xb;
    return xa;
}

//ALGORYTM Z - ZRODLO: https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
void getZarr(string xstr,int xnum)
{
    int xn = xstr.length();
    int xL, xR, xk;

    // [L,R] make a window which matches with prefix of s
    xL = xR = 0;
    for (int i = 1; i < xn; ++i)
    {
        // if i>R nothing matches so we will calculate.
        // Z[i] using naive way.
        if (i > xR)
        {
            xL = xR = i;

            // R-L = 0 in starting, so it will start
            // checking from 0'th index. For example,
            // for "ababab" and i = 1, the value of R
            // remains 0 and Z[i] becomes 0. For string
            // "aaaaaa" and i = 1, Z[i] and R become 5

            while (xR<xn && xstr[xR-xL] == xstr[xR])
            {
                xR++;
            }

            Z[i] = xR-xL;
            xR--;

        }
        else
        {
            // k = i-L so k corresponds to number which
            // matches in [L,R] interval.
            xk = i-xL;

            // if Z[k] is less than remaining interval
            // then Z[i] will be equal to Z[k].
            // For example, str = "ababab", i = 3, R = 5
            // and L = 2

            if (Z[xk] < xR-i+1)
                Z[i] = Z[xk];

            // For example str = "aaaaaa" and i = 2, R is 5,
            // L is 0
            else
            {
                // else start from R and check manually

                xL = i;
                while (xR<xn && xstr[xR-xL] == xstr[xR])
                {
                    xR++;
                }
                Z[i] = xR-xL;
                xR--;

            }
        }
        if(Z[i]==xnum&&i>xnum&&i+k<xstr.length())
        {
            ile[num][xstr[i+k]-'a']++;
            //cout<<i+k<<" "<<xstr[i+k]-'a'<<"\n";
        }
    }
}

int ilen;
bool czy;

bool czycykl()
{
    if((cykl.length())%2==1)
    {
        return 0;
    }

    for(int i=0;i<cykl.length()/2;i++)
    {
        if(cykl[i]!=cykl[i+(cykl.length()/2)]) return 0;
    }

    return 1;
}

string ostk()
{
    string xsk="";

    for(int i=s.length()-k;i<s.length();i++)
    {
        xsk+=s[i];
    }

    return xsk;
}

///////////////////////////////////////////////////////////////////
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k>>a>>b;
    cin>>s;
    ps=s;

    czy=1;
    num=1;
    while(czy)
    {
        sk=ostk();
        if(mapa.find(sk)==mapa.end()) //nie bylo
        {
            mapa[sk]=num;
            getZarr(sk+"&"+s,sk.length());
            //cout<<sk+"&"+s<<" ";

            ilen=0;

            mxlit[num]='a';
            for(int i=0;i<26;i++)
            {
                if(ile[num][i]>ilen)
                {
                    ilen=ile[num][i];
                    mxlit[num]=('a'+i);
                }
            }
            //cout<<mxlit[num]<<"\n";

            num++;
        }

        if(mapa.find(sk)!=mapa.end()) s+=mxlit[mapa[sk]];
        if(mapa.find(sk)!=mapa.end()) cykl+=mxlit[mapa[sk]];

        //cout<<cykl<<" ";

        if(czycykl()) czy=0;
    }

    /*cout<<cykl.length()<<"\n";
    for(int i=0;i<cykl.length();i++) cout<<cykl[i]<<" ";*/


    a-=n;
    b-=n;

    for(ll i=a;i<=b;i++)
    {
        cout<<cykl[(i-1+cykl.length())%cykl.length()];
        //if((i-1+cykl.length())%cykl.length()>=cykl.length()||(i-1+cykl.length())%cykl.length()<0) cout<<"z";
    }

    //cout<<"a";

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
