#include <bits/stdc++.h>
#include <fstream>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n=153;
string s;
string data[10005];
int mal[10005], po[10005], tru[10005];
int mp,mt,pt,mpk,mtk,ptk;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fstream plik;
    plik.open("owoce.txt");
    plik >> s >>s>>s>>s;

    for(int i=1;i<=n;i++)
    {
        plik>>data[i]>>mal[i]>>tru[i]>>po[i];
    }

    for(int i=1;i<=n;i++)
    {
        if(mal[i]<po[i]&&mal[i]<tru[i])
        {
            pt++;
            mal[i+1]+=mal[i];
            int h=min(tru[i],po[i]);
            tru[i]-=h;
            po[i]-=h;
            ptk+=h;

            tru[i+1]+=tru[i];
            po[i+1]+=po[i];
        }
        else if(po[i]<mal[i]&&po[i]<tru[i])
        {
            mt++;
            po[i+1]+=po[i];
            int h=min(mal[i],tru[i]);
            mal[i]-=h;
            tru[i]-=h;
            mtk+=h;

            mal[i+1]+=mal[i];
            tru[i+1]+=tru[i];
        }
        else
        {
            mp++;
            tru[i+1]+=tru[i];
            int h=min(mal[i],po[i]);
            mal[i]-=h;
            po[i]-=h;
            mpk+=h;

            mal[i+1]+=mal[i];
            po[i+1]+=po[i];
        }
    }

    cout<<mp<<" "<<mt<<" "<<pt<<"\n"<<mpk<<" "<<mtk<<" "<<ptk;



    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
