#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;

struct node
{
    int val;
    ll sum;
    int cnt;

    int h;
    int bal;

    struct node* l;
    struct node* r;

    node(int _val)
    {
        val = _val;
        sum = _val;
        cnt = 1;
        h = 0;
        bal = 0;
        l = nullptr;
        r = nullptr;
    }
};

void upt(struct node* tree)
{
    if(tree == nullptr) return;
    tree->val = 0;
    tree->sum = tree->l->sum + tree->r->sum;
    tree->h = max(tree->l->h,tree->r->h)+1;
    tree->bal = tree->l->h - tree->r->h;
    tree->cnt = tree->l->cnt + tree->r->cnt;
};

struct node* rotr(struct node* tree)
{
    struct node* x = tree->l;
    struct node* y = x->r;

    x->r = tree;
    tree->l = y;

    upt(tree);
    upt(x);

    return x;
}

struct node* rotl(struct node* tree)
{
    struct node* y = tree->r;
    struct node* x = y->l;

    y->l = tree;
    tree->r = x;

    upt(tree);
    upt(y);

    return y;
}

struct node* rebalance(struct node* tree)
{
    if (tree == nullptr) return tree;
    upt(tree);

    if (tree->bal > 1 && tree->l->bal >= 0) return rotr(tree); // right rotation

    if (tree->bal < -1 && tree->r->bal <= 0) return rotl(tree); // left rotation

    if (tree->bal > 1 && tree->l->bal < 0) // left right rotation
    {
        tree->l = rotl(tree->l);
        return rotr(tree);
    }

    if (tree->bal < -1 && tree->r->bal > 0) // right left rotation
    {
        tree->r = rotr(tree->r);
        return rotl(tree);
    }

    return tree;
}

struct node* ins(struct node* tree, int x, int p)
{
    if(p == 0 && tree->cnt == 1)
    {
        struct node* newnode = new node(x);

        struct node* newpar = new node(0);
        newpar->r = tree;
        newpar->l = newnode;
        upt(newpar);

        return newpar;
    }
    else if(p == 1 && tree->cnt == 1)
    {
        struct node* newnode = new node(x);

        struct node* newpar = new node(0);
        newpar->l = tree;
        newpar->r = newnode;
        upt(newpar);

        return newpar;
    }
    else if(p <= tree->l->cnt)
    {
        tree->l = ins(tree->l, x, p);
    }
    else if(tree->l->cnt < p)
    {
        tree->r = ins(tree->r, x, p-tree->l->cnt);
    }
    else
    {
        //cout << "error";
    }

    return rebalance(tree);
};

struct node* rmv(struct node* tree, int p)
{
    if(p == 1 && tree->cnt == 1) // jestesmy w usuwanym lisciu
    {
        delete(tree);
        return nullptr;
    }
    else if(tree->l->cnt >= p)
    {
        tree->l = rmv(tree->l,p);
        if(tree->l == nullptr)
        {
            struct node* temp = tree->r;
            delete(tree);
            return temp;
        }
    }
    else if(tree->l->cnt < p)
    {
        tree->r = rmv(tree->r, p-tree->l->cnt);
        if(tree->r == nullptr)
        {
            struct node* temp = tree->l;
            delete(tree);
            return temp;
        }
    }
    return rebalance(tree);
};

ll query(struct node* tree, int x, int y)
{
    if(x <= 1 && tree->cnt <= y) return tree->sum;

    ll sum = 0;
    if(x <= tree->l->cnt) sum += query(tree->l, x, y);
    if(tree->l->cnt < y) sum += query(tree->r, x-tree->l->cnt, y-tree->l->cnt);
    return sum;
}

void printt(struct node* tree)
{
    if(tree->l == nullptr) cout << tree->val << " ";
    else
    {
        printt(tree->l);
        printt(tree->r);
    }
}

struct node* tree = nullptr;

ll operacjaavl(char zap, int a, int b)
{
    if(zap == 'I')
    {
        if(a == 0 && tree == nullptr)
        {
            tree = new node(b);
        }
        else if(tree != nullptr)
        {
            tree = ins(tree, b, a);
        }
        else
        {
            //cout << "error";
        }
        //printt(tree);
        //cout<<"   h: "<<tree->h<<"\n";
    }
    else if(zap == 'S')
    {
        return query(tree, a, b);
        //printt(tree);
        //cout<<"   h: "<<tree->h<<"\n";
    }
    else if(zap == 'D')
    {
        tree = rmv(tree, a);
        //printt(tree);
        //cout<<"   h: "<<tree->h<<"\n";
    }
    return 0;
}

int tab[1000005];

ll operacjabrut(char zap, int a, int b)
{
    if(zap == 'I')
    {
        for(int i=1000000;i>=a+2;i--)
        {
            tab[i]=tab[i-1];
        }
        tab[a+1]=b;
    }
    else if(zap == 'S')
    {
        ll sum = 0;
        for(int i=a;i<=b;i++) sum+=tab[i];
        return sum;
    }
    else if(zap == 'D')
    {
        for(int i=a;i<1000000;i++)
        {
            tab[i]=tab[i+1];
        }
        tab[1000000]=0;
    }
    return 0;
}

int rnd(int a, int b)
{
    int los = rand() % (b-a+1);
    return los+a;
}

int main()
{
    srand(time(0));

    int k;
    cin >> k;

    int n=0;
    int zap;
    char zapp;
    int a,b;
    bool czy;
    while(k--)
    {
        czy=0;
        while(!czy)
        {
            zap=rnd(3,100);
            czy=1;
            if(zap == 3 && n<1) czy=0;
            if(zap>3 && zap<=50 && n<1) czy=0;
        }
        //cout<<zap<<" ";
        czy=0;
        if(zap>50)
        {
            a = rnd(0,n);
            b = rnd(-10000, 10000);
            zapp='I';
            n++;
        }
        if(zap>3 && zap<=50)
        {
            a = rnd(1,n);
            b = rnd(1,n);
            if(a>b) swap(a,b);
            zapp='S';
        }
        if(zap == 3)
        {
            a = rnd(1,n);
            zapp='D';
            n--;
        }
        //cout <<a<<" "<<b<<"\n";
        if(operacjaavl(zapp,a,b) != operacjaavl(zapp,a,b))
        {
            cout<<"KURWA ERROR KURWA ERROR\n";
            cout<<operacjaavl(zapp,a,b)<<" "<< operacjabrut(zapp,a,b)<<"\n";
        }

    }


    return 0;
}
