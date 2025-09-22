#include <stdlib.h>
#include <stdio.h>

struct listEl
{
    int i;
    int j;
    struct listEl* pre;
    struct listEl* next;
};

struct node
{
    char war;
    struct listEl* elem;
};

int a;
int n,m;
long long wynik=0;
struct listEl* lista[10];
struct node* tab[51][51];
char lic = 9;
int start = 0;

void inic()
{
    for(int i=0; i<=9; i++)
    {
        lista[i] = (struct listEl*)malloc(sizeof(struct listEl));
        lista[i]->i = 0;
        lista[i]->j = 0;
        lista[i]->next = NULL;
        lista[i]->pre = NULL;
    }

    for(int i=1; i<=50; i++)
    {
        for(int j=1; j<=50; j++)
        {
            tab[i][j] = (struct node*)malloc(sizeof(struct node));
        }
    }
}

void move(struct listEl* co, int dokad)
{
    if(tab[co->i][co->j]->war == lic && start == 1) 
    {
        //printf("zle %d %d %d\n", co->i, co->j, dokad);
        return;
    }
    //printf("git %d %d %d %d\n", co->i, co->j, dokad, tab[co->i][co->j]->war);

    if(co->pre != NULL) co->pre->next = co->next;
    if(co->next != NULL) co->next->pre = co->pre;

    if(lista[dokad]->pre != NULL) lista[dokad]->pre->next = co;
    co->pre = lista[dokad]->pre;
    lista[dokad]->pre = co;
    co->next = lista[dokad];


    tab[co->i][co->j]->war = dokad;
}

void wypisz(int num)
{
    struct listEl* ptr = lista[num]->pre;
    while(ptr != NULL)
    {
        //printf("i:%d j:%d\n", ptr->i, ptr->j);
        ptr = ptr->pre;
    }
}

struct listEl* dol(int num)
{
    struct listEl* ptr = lista[num];
    while(ptr->pre != NULL) ptr = ptr->pre;
    return ptr;
}

void zaswiec(struct listEl* ptr)
{
    //printf("wtffffffffffff %d %d\n", ptr->i, ptr->j);
    if((ptr->i)-1 >= 1 && (ptr->i)+1 <= n)
    {
        //printf("check %d %d\n", ((tab[(ptr->i)-1][ptr->j]->war)+1)%10, ((tab[(ptr->i)+1][ptr->j]->war)+1)%10);
        move(tab[(ptr->i)-1][ptr->j]->elem, ((tab[(ptr->i)-1][ptr->j]->war)+1)%10);
        move(tab[(ptr->i)+1][ptr->j]->elem, ((tab[(ptr->i)+1][ptr->j]->war)+1)%10);

        if((ptr->j)-1 >= 1)
        {
            move(tab[(ptr->i)][(ptr->j)-1]->elem, (tab[(ptr->i)][(ptr->j)-1]->war+1)%10);
            move(tab[(ptr->i)-1][(ptr->j)-1]->elem, (tab[(ptr->i)-1][(ptr->j)-1]->war+1)%10);
            move(tab[(ptr->i)+1][(ptr->j)-1]->elem, (tab[(ptr->i)+1][(ptr->j)-1]->war+1)%10);
        }
        if((ptr->j)+1 <= n)
        {
            move(tab[(ptr->i)][(ptr->j)+1]->elem, (tab[(ptr->i)][(ptr->j)+1]->war+1)%10);
            move(tab[(ptr->i)-1][(ptr->j)+1]->elem, (tab[(ptr->i)-1][(ptr->j)+1]->war+1)%10);
            move(tab[(ptr->i)+1][(ptr->j)+1]->elem, (tab[(ptr->i)+1][(ptr->j)+1]->war+1)%10);
        }
    }
    else if((ptr->i)-1 >= 1)
    {
        move(tab[(ptr->i)-1][ptr->j]->elem, (tab[(ptr->i)-1][ptr->j]->war+1)%10);

        if((ptr->j)-1 >= 1)
        {
            move(tab[(ptr->i)][(ptr->j)-1]->elem, (tab[(ptr->i)][(ptr->j)-1]->war+1)%10);
            move(tab[(ptr->i)-1][(ptr->j)-1]->elem, (tab[(ptr->i)-1][(ptr->j)-1]->war+1)%10);
        }
        if((ptr->j)+1 <= n)
        {
            move(tab[(ptr->i)][(ptr->j)+1]->elem, (tab[(ptr->i)][(ptr->j)+1]->war+1)%10);
            move(tab[(ptr->i)-1][(ptr->j)+1]->elem, (tab[(ptr->i)-1][(ptr->j)+1]->war+1)%10);
        }
    }
    else if((ptr->i)+1 <= n)
    {
        move(tab[(ptr->i)+1][ptr->j]->elem, (tab[(ptr->i)+1][ptr->j]->war+1)%10);

        if((ptr->j)-1 >= 1)
        {
            move(tab[(ptr->i)][(ptr->j)-1]->elem, (tab[(ptr->i)][(ptr->j)-1]->war+1)%10);
            move(tab[(ptr->i)+1][(ptr->j)-1]->elem, (tab[(ptr->i)+1][(ptr->j)-1]->war+1)%10);
        }
        if((ptr->j)+1 <= n)
        {
            move(tab[(ptr->i)][(ptr->j)+1]->elem, (tab[(ptr->i)][(ptr->j)+1]->war+1)%10);
            move(tab[(ptr->i)+1][(ptr->j)+1]->elem, (tab[(ptr->i)+1][(ptr->j)+1]->war+1)%10);
        }
    }
    
}

void update(int x)
{
    struct listEl* ptr = dol(x);
    while(ptr->next != NULL)
    {
        //printf("%d %d\n", ptr->i, ptr->j);
        wynik++;
        zaswiec(ptr);
        ptr = ptr->next;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    inic();

    char c;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            scanf("%c", &c);
            if(c == '\n') scanf("%c", &c);
            a = (int)(c - '0');
            //printf("%c", c);
            tab[i][j]->war = a;
            struct listEl* newel = (struct listEl*)malloc(sizeof(struct listEl));
            newel->i = i;
            newel->j = j;
            newel->next = NULL;
            newel->pre = NULL;
            tab[i][j]->elem = newel;
            move(newel, a);
        }
    }

    /*for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            printf("%d ", tab[i][j]->war);
        }
        printf("\n");
    }
    //printf("%d %d %d %d", tab[3][4]->elem->pre->i, tab[3][4]->elem->pre->j, tab[3][4]->elem->next->i, tab[3][4]->elem->next->j);
    move(tab[2][2]->elem, 5);
    move(tab[4][4]->elem, 4);

    for(int i=0; i<=9; i++)
    {
        printf("\n");
        wypisz(i);
    }
    */
   
    

    start = 1;
    for(int ii = 0; ii<m; ii++)
    {
        update(lic);
        lic--;
        if(lic<0) lic=9;

        /*for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                printf("%d ", tab[i][j]->war);
            }
            printf("\n");
        }
        printf("\n");*/
    }
    printf("%lld", wynik);
}