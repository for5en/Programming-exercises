#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

string s;
int ile,mn,id;
char c;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>s;

    id=0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]!='*')
        {
            id=i;
            i=s.length();
        }

    }

    c=s[id];
    czy=1;

    for(int i=id+1;i<s.length();i++)
    {
        if(s[i]!='*')
        {
            if(s[i]!=c)
            {
                czy=0;
            }
        }
    }

    if(czy)
    {
        cout<<"1";
        return 0;
    }
    else if(s[0])



    return 0;
}
