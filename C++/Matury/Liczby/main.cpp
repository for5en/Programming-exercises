#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int tab[510];
bitset <100010> pot;
int silnie[15];

void preproc()
{
    for(int i=1;i<=100000;i*=3)
    {
        pot[i]=1;
    }

    silnie[0]=1;
    for(int i=1;i<=9;i++)
    {
        silnie[i]=silnie[i-1]*i;
    }
}

int ss(int x)
{
    int w=0;
    while(x>0)
    {
        w+=silnie[x%10];
        x/=10;
    }

    return w;
}

int main()
{
    fstream plik;
    plik.open("liczby.txt");

    int n=500;
    preproc();

    for(int i=1;i<=500;i++)
    {
        plik >> tab[i];
    }


    // zadanie 4.1
    int odp1=0;
    for(int i=1;i<=n;i++)
    {
        if(pot[tab[i]]) odp1++;
    }


    // zadanie 4.2
    int odp2=0;
    for(int i=1;i<=n;i++)
    {
        if(ss(tab[i])==tab[i]) cout<<tab[i]<<"\n";
    }


    // zadanie 4.3
    int odp3p=0;
    int odp3d=0;
    int odp3dl=0;

    for(int p=2;p*p<=100000;p++)
    {
        // p - dzielnik
        int ak=0;
        for(int i=1;i<=n;i++)
        {
            if(tab[i]%p == 0) ak++;
            else ak=0;

            if(odp3dl<=ak)
            {
                odp3dl=ak;
                odp3p=tab[i-ak+1];
                odp3d=p;
            }
        }
    }

    cout<<"zad1 "<<odp1<<"\nzad2 "<<odp2<<"\nzad3\n"<<odp3p<<" "<<odp3dl<<" "<<odp3d;


    return 0;
}
