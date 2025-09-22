#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// STRUKTURA DRZEWA
struct node
{
    int kol;
    int wie;
    struct node* ojciec;
    struct node** dzieci;
};

// FUNKCJA TWORZACA PODDRZEWO 
struct node* gentree(int n, struct node* x, int wie)
{
    if(x->kol >= n-1)
    {
        return NULL;
    }

    struct node* syn = (struct node*)malloc(sizeof(struct node));
    if(syn == NULL)
    {
        printf("blad1\n");
        return NULL;
    }
    
    syn->dzieci = (struct node**)malloc(sizeof(struct node*) * n);
    if(syn->dzieci == NULL) 
    {
        printf("blad2\n");
        return NULL;
    }

    syn->wie = wie;
    syn->kol = x->kol + 1;
    syn->ojciec = x;

    for(int i=0; i<n; i++)
    {
        syn->dzieci[i] = (struct node*)malloc(sizeof(struct node));
        if(syn->dzieci[i] == NULL)
        {
            printf("blad3\n");
            return NULL;
         }       
        syn->dzieci[i] = gentree(n, syn, i);
    }

    return syn;
}
// syn dwa razy alokowany
// check 

// FUNKCJA TWORZACA DRZEWO
// implementuje drzewo w taki sposob aby miec pierwotny wierzcholek od ktorego wychodzi kolumna 0, a do tego potrzebowalem wiecej 
// kodu niz jedynie wywolanie funkcji (a przynajmniej w moim z pewnoscia nieoptymalnym rozwiazaniu), stad taka funkcja przechodnia
struct node* gendrzewo(int n)
{
    struct node* korzen = (struct node*)malloc(sizeof(struct node));
    if(korzen == NULL) return NULL;

    korzen->dzieci = (struct node**)malloc(sizeof(struct node*) * n);
    if(korzen->dzieci == NULL) return NULL;

    korzen->kol = -1;
    for(int i=0; i<n; i++)
    {
        korzen->dzieci[i] = gentree(n, korzen, i);
    }

    korzen->ojciec = NULL;

    return korzen;
}


// FUNKCJA SPRAWDZAJACA CZY PODANE POLE JEST DOSTEPNY - TZN. NIE BITY
// ZWRACA NUMER KOLUMNY HETMANA KTORY BIJE PODANE POLE LUB -2 GDY POLE JEST WOLNE
int check(struct node* x)
{
    struct node* ptr = x->ojciec;
    while(ptr != NULL)
    {
        if((ptr->wie == x->wie || (ptr->kol + x->wie == x->kol + ptr->wie) || (ptr->kol + ptr->wie == x->kol + x->wie)) && ptr->kol != -1) 
        {
            return ptr->kol;
        }
        ptr = ptr->ojciec;
    }
    return -2;
}


// FUNKCJA KTORA WYPISUJE PREFIX DRZEWA NA PODSTAWIE MASKI BITOWEJ
void poczatek(long long x, int dep)
{
    if(dep <= 0) return;
    poczatek(x/2, dep-1);

    if(x%2 == 1) printf("| ");
    else printf("  ");
}


// FUNKCJA WYPISUJACA DRZEWO
void wypisz(struct node* x, int n, long long pocz, int dep)
{
    // GDY WIERZCHOLEK NIE MA DZIECI TO RETURN
    if(x->dzieci == NULL) return;


    int kol;

    for(int i=0; i<n; i++)
    {
        // GDY SYN ISTNIEJE
        if(x->dzieci[i] != NULL)
        {
            // SPRAWDZAM CZY POLE JEST DOSTEPNE
            kol = check(x->dzieci[i]);

            if(kol == -2) // JESLI POLE JEST DOSTEPNE TO
            {
                poczatek(pocz, dep); // WYPISUJE PREFIX DRZEWOWY
                // WYPISUJE INFORMACJE O PODANYM POLU - JESLI BYLA TO OSTATNIA KOLUMNA TO SUKCES
                if(x->dzieci[i]->kol == n-1) printf("+-\\ Kolumna %d wiersz %d nie jest atakowana, stawiamy hetmana - SUKCES!\n", x->dzieci[i]->kol, x->dzieci[i]->wie);
                else printf("+-\\ Kolumna %d wiersz %d nie jest atakowana, stawiamy hetmana\n", x->dzieci[i]->kol, x->dzieci[i]->wie);

                // PODAJE REKURENCJE DO DALSZYCH SYNOW AKTUALIZUJAC PREFIX DRZEWOWY NA PODSTAWIE NUMERU WIERSZA
                if(x->dzieci[i]->wie == n-1) wypisz(x->dzieci[i], n, pocz<<1, dep+1);
                else wypisz(x->dzieci[i], n, (pocz<<1) + 1, dep+1);
            }
            else // JESLI POLE JEST NIEDOSTEPNE TO
            {
                // WYPISUJE PREFIX DRZEWOWY I INFORMACJE O POLU
                poczatek(pocz, dep);
                printf("+-- Kolumna %d wiersz %d jest atakowany przez hetmana z kolumny %d\n", x->dzieci[i]->kol, x->dzieci[i]->wie, kol);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int n;

    if(argc != 2) return 1;
    else
    {
        char *blad;
        n = strtol(argv[1], &blad, 10);
        if(strlen(blad) > 0) return 1;
    }

    struct node* drzewo = gendrzewo(n);
    wypisz(drzewo, n, 0,0);
}