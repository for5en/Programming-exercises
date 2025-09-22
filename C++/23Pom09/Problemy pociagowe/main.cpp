#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int q,n,a,odp;

int mn; //minimalny czas
int ile; //ile ludzi w wagonie
int t; //czas

bitset <5000010> sito;
vector <int> v1,v2,v3;

void gensito()
{
    for(int i=4;i<=5000000;i+=2)
    {
        sito[i]=1;
    }

    for(int i=3;i<=5000000;i+=2)
    {
        if(sito[i]==0)
        {
            for(int j=i+i;j<=5000000;j+=i)
            {
                sito[j]=1;
            }
        }
    }

    for(int i=2;i<=5000000;i++)
    {
        if(sito[i]==0)
        {
            //cout<<"dupa"<<i<<"\n";
            if(i%4==1)
            {
                v1.pb(i);
            }
            else if(i%4==2)
            {
                v2.pb(i);
            }
            else if(i%4==3)
            {
                v3.pb(i);
            }
        }
    }
}

int oblicz(int x)
{
    //cout<<x<<"\n";
    if(x%4==0) return x/4+1;
    int h;

    if(x%4==1)
    {
        //cout<<"d";
        h=*(upper_bound(v1.begin(),v1.end(),x)-1);
        //cout<<"d";
    }
    else if(x%4==2)
    {
        h=*(upper_bound(v2.begin(),v2.end(),x)-1);
    }
    else if(x%4==3)
    {
        h=*(upper_bound(v3.begin(),v3.end(),x)-1);
    }

    x-=h;

    return ((x/4)+1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>q;

    gensito();

    /*cout<<"\n\n"<<"v1"<<"\n";
    for(int i=0;i<v1.size();i++)
    {
        cout<<v1[i]<<" ";
    }

    cout<<"\n\n"<<"v2"<<"\n";
    for(int i=0;i<v2.size();i++)
    {
        cout<<v2[i]<<" ";
    }

    cout<<"\n\n"<<"v3"<<"\n";
    for(int i=0;i<v3.size();i++)
    {
        cout<<v3[i]<<" ";
    }*/


    for(int ii=0;ii<q;ii++)
    {
        cin>>n;
        mn=999999999;

        for(int i=1;i<=n;i++)
        {
            cin>>a;
            t=oblicz(a);

            if(t<mn)
            {
                ile=a;
                mn=t;
            }
        }
        if(ile%4==0)
        {
            cout<<"Bonifacy\n";
        }
        else
        {
            cout<<"Filemon\n";
        }
    }




    return 0;
}
