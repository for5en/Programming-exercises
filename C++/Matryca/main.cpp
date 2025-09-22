#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

string s;
char p,a;
int ile,mn;
int id;
int gw1,gw2,gs;
bool czy=1;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>s;

    for(int i=0;i<s.length();i++)
    {
        if(s[i]!='*')
        {
            id=i;
            p=s[i];
            i=s.length();
        }
        else
        {
            gw1++;
        }
    }

    for(int i=s.length()-1;i>0;i--)
    {
        if(s[i]=='*') gw2++;
        else i=0;
    }

    mn=999999999;

    for(int i=id+1;i<s.length();i++)
    {
        if(s[i]=='*')
        {
            ile++;
            gs++;
            //cout<<i;
        }
        else if(s[i]!=p)
        {
            //cout<<ile<<" ";
            mn=min(ile,mn);
            p=s[i];
            czy=0;
            ile=0;
        }
        else
        {
            ile=0;
        }
    }

    if(mn==999999999&&czy==1) cout<<"1\n";
    else if(mn==999999999&&czy==0) cout<<s.length()<<"\n";
    else cout<<s.length()-max(mn,min(gw1,gw2))<<"\n";



    return 0;
}
