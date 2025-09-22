#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;

int n, m, taba[500005], tabb[500005];
vector<pair<int, int>>kolumny[100005], wiersze[100005];

vector<int>v[500005], cycle;
int pcyklu,kcyklu;
bool odw[500005];
bool czy;
bool dfs(int p, int s, int k)
{
    odw[p] = 1;
    for(int i=0; i<v[p].size(); i++)
    {
        if(odw[v[p][i]] == 0 && czy == 0)
        {
            if(taba[v[p][i]] == taba[p])
            {
                if(dfs(v[p][i], p, 0) == 1)
                {
                    if(p == pcyklu)
                    {
                        if(taba[kcyklu] != taba[v[p][i]] && tabb[kcyklu] != tabb[v[p][i]]) cycle.pb(p);
                        return 0;
                    }

                    if(k == 1) cycle.pb(p);
                    return 1;
                }
            }
            else
            {
                if(dfs(v[p][i], p, 1) == 1)
                {
                    if(p == pcyklu)
                    {
                        if(taba[kcyklu] != taba[v[p][i]] && tabb[kcyklu] != tabb[v[p][i]]) cycle.pb(p);
                        return 0;
                    }

                    if(k == 0) cycle.pb(p);
                    return 1;
                }
            }
        }
        else if(v[p][i] != s && czy == 0)
        {
            czy = 1;
            pcyklu = v[p][i];
            kcyklu = p;
            if(taba[v[p][i]] == taba[p])
            {
                if(k == 1) cycle.pb(p);
                return 1;
            }
            else
            {
                if(k == 0) cycle.pb(p);
                return 1;
            }
        }
    }
}

vector<int>przyciski;
bool zajwiersze[25], zajkolumny[25];

bool sprawdz()
{
    for(int i=1;i<=n;i++)
    {
        if(zajwiersze[i] == 0 || zajkolumny[i] == 0) return 0;
    }
    return 1;
}

bool m20(int x)
{
    for(int i=1; i<=m; i++)
    {
        if(zajwiersze[taba[i]] == 0 && zajkolumny[tabb[i]] == 0)
        {
            zajwiersze[taba[i]] = 1;
            zajkolumny[tabb[i]] = 1;

            if(m20(i))
            {
                przyciski.pb(x);
                return 1;
            }
            else
            {
                zajwiersze[taba[i]] = 0;
                zajkolumny[tabb[i]] = 0;
            }
        }
    }

    if(sprawdz() == 1)
    {
        przyciski.pb(x);
        return 1;
    }

    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b;
    cin>>n>>m;
    for(int i=1; i<=m; i++)
    {
        cin >> a >> b;
        wiersze[a].pb({b, i});
        kolumny[b].pb({a, i});
        taba[i] = a;
        tabb[i] = b;
    }

    // parzyste Ci i Ri
    if(m >= 4)
    {
        for(int i=1; i<=n; i++)
        {
            if(wiersze[i].size() >= 1)
            {
                sort(wiersze[i].begin(), wiersze[i].end());
                for(int j=1; j<wiersze[i].size(); j++)
                {
                    v[wiersze[i][j-1].ss].pb(wiersze[i][j].ss);
                    v[wiersze[i][j].ss].pb(wiersze[i][j-1].ss);
                }
            }
            if(kolumny[i].size() >=1)
            {
                sort(kolumny[i].begin(), kolumny[i].end());
                for(int j=1; j<kolumny[i].size(); j++)
                {
                    v[kolumny[i][j-1].ss].pb(kolumny[i][j].ss);
                    v[kolumny[i][j].ss].pb(kolumny[i][j-1].ss);
                }
            }
        }

        for(int i=1; i<=m; i++)
        {
            czy = 0;
            if(odw[i] == 0) dfs(i, 0, -1);
            if(czy == 1)
            {
                cout << "TAK\n" << cycle.size() << "\n";
                sort(cycle.begin(), cycle.end());
                for(int j=0; j<cycle.size(); j++) cout << cycle[j] << " ";
                return 0;
            }
        }
    }
    else if(m <= 20 && n <= 20) // nieparzyste Ci i Ri - dla m <= 20
    {
        if(m20(0) == 1)
        {
            cout << "TAK\n" << przyciski.size()-1 << "\n";
            sort(przyciski.begin(), przyciski.end());
            for(int i=1; i<przyciski.size(); i++)
            {
                cout << przyciski[i] << " ";
            }
            return 0;
        }
    }

    cout << "NIE";

    return 0;
}
