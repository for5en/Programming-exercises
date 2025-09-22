#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
const int maxn=1e6;

string ciag, dod;
map<pair<int, int>, int>m;

ll phsh, phsh2, hsh, hsh2;

ll potp[maxn+5]; //potegi p
ll potp2[maxn+5];

char tab[2*maxn+5]; //jaka litera wystepuje najczesciej po sufiksie o numerze i
int tabpom[maxn+2][29]; //zliczanie liter po ciagch o dl k
int czywysigdzie[2*maxn+5];

int p=31, licz=0;
int mod=1e9+7, mod2=1e9+9;

ll n, k, a, b;

int kta(int l)
{
    return ciag[l]-'a'+1;
}

void upot()
{
    potp[0]=1;
    potp2[0]=1;
    for(int i=1; i<=k; i++)
    {
        potp[i]=(potp[i-1]*p)%mod;
        potp2[i]=(potp2[i-1]*p)%mod2;
    }
}

void prephsh()
{
    ll pom=0, pom2=0;
    for(int i=0; i<k; i++)
    {
        pom+=(kta(i)*potp[k-i])%mod;
        pom%=mod;
        pom2+=(kta(i)*potp2[k-i])%mod2;
        pom2%=mod;
    }

    phsh=pom;
    phsh2=pom2;
    m[{pom, pom2}]=licz+1;
    licz++;

    for(int i=k; i<n; i++)
    {
        hsh=(phsh-potp[k]*kta(i-k)+kta(i))*p;
        hsh%=mod;
        hsh2=(phsh2-potp2[k]*kta(i-k)+kta(i))*p;
        hsh2%=mod2;
        while(hsh<0) hsh+=mod;
        while(hsh2<0) hsh2+=mod2;
        tabpom[m[{phsh, phsh2}]][kta(i)]++; //dodaj literkê na której teraz jesteœmy do wystêpuj¹cych w poprzednim suf

        if(m[{hsh, hsh2}]==0)
        {
            m[{hsh, hsh2}]=licz+1;
            licz++;
        }
        phsh=hsh;
        phsh2=hsh2;
    }
}

void utab()
{
    int maxx=0;
    char ix;
    bool czy=0;
    for(int i=1; i<=licz; i++)
    {
        for(int j=1; j<=27; j++)
        {
            if(maxx<tabpom[i][j])
            {
                ix=j;
                maxx=tabpom[i][j];
                czy=1;
            }
        }

        if(czy==1) tab[i]=ix+'a'-1;
        else tab[i]='a';
        maxx=0;
        czy=0;
    }
}

void uhsh(int t)
{
    hsh=(phsh-potp[k]*kta(t-k)+kta(t))*p;
    hsh%=mod;
    hsh2=(phsh2-potp2[k]*kta(t-k)+kta(t))*p;
    hsh2%=mod2;
    while(hsh<0) hsh+=mod;
    while(hsh2<0) hsh2+=mod2;
    tab[m[{phsh, phsh2}]]=ciag[t];

    phsh=hsh;
    phsh2=hsh2;
}

bool czyktoa()
{
    for(int i=ciag.length()-k;i<ciag.length();i++)
    {
        if(ciag[i]!='a') return 0;
    }
    return 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll pom=-1, dlcyklu, odktoregocykl;
    cin >> n >> k >> a >> b >> ciag;
    a=a-n-1;
    b=b-n-1;

    upot();
    prephsh();
    utab();

    while(czywysigdzie[m[{hsh, hsh2}]]==0)
    {
        ciag.pb(tab[m[{hsh, hsh2}]]);
        dod.pb(tab[m[{hsh, hsh2}]]);
        czywysigdzie[m[{hsh, hsh2}]]=pom+2;
        uhsh(n+pom+1);
        if(czyktoa())
        {
            czywysigdzie[0]=pom+3;
            hsh=0;
            hsh2=0;
            m[{0,0}]=licz+1;
            licz++;
        }
        pom++;
    }
    dlcyklu=dod.size()-czywysigdzie[m[{hsh, hsh2}]]+1;
    pom=dod.size();
    odktoregocykl=pom-dlcyklu;

    for(a; a<dod.size() && a<=b; a++) cout << dod[a];
    for(a; a<=b; a++) cout << dod[(a-odktoregocykl)%dlcyklu+odktoregocykl];
    cout << "\n";


    return 0;
}
