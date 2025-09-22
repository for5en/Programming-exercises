#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

int n;
char zap;
int a,b;

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
    if(tree == nullptr) return;
    if(tree->l == nullptr) cout << tree->val << " ";
    else
    {
        printt(tree->l);
        printt(tree->r);
    }
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);*/

    struct node* tree = nullptr;

    cin >> n;

    while(n--)
    {
        cin >> zap;
        if(zap == 'I')
        {
            cin >> a >> b;
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
            //cout<<"\n";
        }
        else if(zap == 'S')
        {
            cin >> a >> b;
            cout << query(tree, a, b) << "\n";
            //printt(tree);
            //cout<<"\n";
        }
        else if(zap == 'D')
        {
            cin >> a;
            tree = rmv(tree, a);
            //printt(tree);
            //cout<<"\n";
        }
    }


    return 0;
}
