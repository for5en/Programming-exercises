#include <bits/stdc++.h>

    using namespace std;

        int a,b,c;
        vector <pair <int,int>> v;


    int main()
    {

        cin>>a;

        for(int i=0;i<=a-1;i++)
        {

            cin>>b>>c;

            v.push_back({b,c});

        }

        sort(v.begin(),v.end());

        for(int i=a-1;i>=0;i--)
        {
            cout<<v[i].first<<" "<<v[i].second<<endl;

        }


        return 0;
    }
