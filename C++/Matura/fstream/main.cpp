#include <bits/stdc++.h>
#include <fstream>


using namespace std;

fstream plik;


int n;
// ilosc

int a[100],b[100];
// liczby a i b

char n1[100],n2[100];
// pierwsze i drugie nawiasy

char srk;
// srednik

int main()
{
    plik.open("nazwa_pliku.txt");
    // WAZNE! PLIK MUSI ZNAJDOWAC SIE W FOLDERZE Z PROGRAMEM!

    n=13;
    // ustawiam n na iloœæ pakietów do wczytania ( w tym przypadku jeden pakiet to [nawias][liczba][srednik][liczba][nawias] )( ilosc wierszy do wczytania... )

    for(int i=1;i<=n;i++)
    {
        plik >> n1[i] >> a[i] >> srk >> b[i] >> n2[i];
        // wczytuje tak jak z cinem, ale zamiast cina jest plik lol
    }

    for(int i=1;i<=n;i++)
    {
        cout << n1[i] << a[i] << srk << b[i] << n2[i] << "\n";
        // wypisuje dane
    }


    return 0;
}
