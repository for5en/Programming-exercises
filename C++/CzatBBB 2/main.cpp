#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n,k,cn;
ll a,b;

string s,cykl;
ll hashx,hashy;
pair <ll,ll> Ahash;

int px=41, py=47;
ll P=999999929;
ll tpx[1000010], tpy[1000010];

int num;
map <pair<ll,ll>,int> hmap;
// klucz-para hashow, numer slowa

int h;
char litk;
char mlitk[1000010];

int popw[1000010];
int xcykl,ycykl;

int tabl[1000010][30];
//tablica ilosci liter po slowie


void preprocess()
{
    tpx[1]=px;
    tpy[1]=py;

    for(int i=2;i<=k;i++)
    {
        tpx[i]=tpx[i-1]*px;
        tpy[i]=tpy[i-1]*py;

        if(tpx[i]>P) tpx[i]%=P;
        if(tpy[i]>P) tpy[i]%=P;
    }
}

void movehash(int pos)
{
    hashx-=(s[pos-k]-'a'+1)*tpx[k];
    hashy-=(s[pos-k]-'a'+1)*tpy[k];

    while(hashx<0) hashx+=P;
    while(hashy<0) hashy+=P;

    hashx*=px;
    hashy*=py;

    hashx+=(s[pos]-'a'+1)*px;
    hashy+=(s[pos]-'a'+1)*py;

    if(hashx>P) hashx%=P;
    if(hashy>P) hashy%=P;
}

void makeAhash()
{
    ll hx=0;
    ll hy=0;

    for(int i=0;i<k;i++)
    {
        hx+=(1)*tpx[k-i];
        hy+=(1)*tpy[k-i];

        if(hx>P) hx%=P;
        if(hy>P) hy%=P;
    }

    Ahash={hx,hy};
}

bool checkcykl()
{
    if(cykl.size()<k) return 0;
    if(hmap.find(Ahash)==hmap.end())
    {
        if(hashx==Ahash.ff&&hashy==Ahash.ss)
        {
            //cout<<"jakimchujem";
            return 1;
        }
    }
    else
    {
        //cout<<"falszmato";
        return 0;
    }
    return 0;
}

string prts(int pos)
{
    string pstr="";
    for(int i=pos-k+1;i<=pos;i++)
    {
        pstr+=s[i];
    }
    return pstr;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k>>a>>b;
    cin>>s;

    preprocess();

    for(int i=0;i<k;i++)
    {
        hashx+=(s[i]-'a'+1)*tpx[k-i];
        hashy+=(s[i]-'a'+1)*tpy[k-i];

        if(hashx>P) hashx%=P;
        if(hashy>P) hashy%=P;
    }
    num++;
    hmap[{hashx,hashy}]=num;
    tabl[num][s[k]-'a']++;
    //cout<<prts(k-1)<<"\n";
    //cout<<"xh "<<hashx<<"\n\n";
    //cout<<hashconnect()<<"\n";

    // preprocessing dla wszystkich slow k w poczatkowym slowie
    for(int i=k;i<s.length()-1;i++)
    {
        movehash(i);
        //if(prts(i)=="tadeusz") cout<<s[i+1]<<"\n";
        //cout<<prts(i)<<"\n";
        //cout<<"hx "<<hashx<<"\n\n";
        //cout<<hashxy<<"\n";
        litk=s[i+1];

        if(hmap.find({hashx,hashy})==hmap.end()) // nie ma slowa w mapie
        {
            num++;
            hmap[{hashx,hashy}]=num;
            tabl[num][litk-'a']++;
        }
        else // slowo jest mapie
        {
            tabl[hmap[{hashx,hashy}]][litk-'a']++;
        }
    }

    // znajdowanie najczesciej wystepujacej literki dla kazdego z poczatkowych slow k
    for(int i=1;i<=num;i++)
    {
        litk='a';
        h=0;

        //cout<<"\n"<<i<<":\n";

        for(int j=0;j<26;j++)
        {
            //cout<<(char)(j+'a')<<","<<tabl[i][j]<<"   ";
            if(tabl[i][j]>h)
            {
                h=tabl[i][j];
                litk=(j+'a');
            }
        }

        mlitk[i]=litk;
        //cout<<i<<" "<<litk<<"\n";
    }

    h=s.length()-1;
    makeAhash();
    bool czy=1;
    while(czy)
    {
        movehash(h);
        h++;

        //cout<<hashxy<<"\n";

        if(hmap.find({hashx,hashy})==hmap.end()) // slowo nie wystapilo
        {
            s+='a';
            cykl+='a';
        }
        else // slowo wystapilo
        {
            if(popw[hmap[{hashx,hashy}]]!=0) // znaleziono cykl
            {
                xcykl=popw[hmap[{hashx,hashy}]];
                ycykl=cn-1;
                czy=0;
                cn--;
                //cout<<"wtf";
            }
            else
            {
                popw[hmap[{hashx,hashy}]]=cn;
                s+=mlitk[hmap[{hashx,hashy}]];
                cykl+=mlitk[hmap[{hashx,hashy}]];
                //cout<<"huikurwa";
            }
        }
        //cout<<cykl<<" ";
        cn++;

        if(checkcykl()) //aaaaa...a }*k
        {
            //cout<<"poebaoKURWA";
            czy=0;
            ycykl=cn-1;
            xcykl=cn-k;
        }
    }

    // wypisywanie z cyklu
    a-=n;
    b-=n;
    a--;
    b--;

    //cout<<xcykl<<"\n";

    if(a<xcykl)
    {
        for(a;a<xcykl;a++)
        {
            cout<<cykl[a];
        }
    }

    for(ll i=a;i<=b;i++)
    {
        cout<<cykl[xcykl + (i-xcykl)%(ycykl-xcykl+1)];
    }

    return 0;
}

// Igor Rostkowski 4EP
// lo3 Gdynia
