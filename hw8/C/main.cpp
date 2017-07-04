#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <map>

using namespace std::chrono;


using namespace std;


vector<uint64_t> v;
vector<uint64_t> vfr;

typedef struct teams
{
    int size;
    int rest;
}teams;

vector<teams> vt;

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);

    int t = 1;

    cin >> t;
    cin.ignore();


    for (int i = 1; i <= t; ++i)
    {
        int n, k, sz_marker = 0;
        teams tt;

        cin >> n >> k;

        for (int j = 0; j < n; ++j)
        {
            cin >>tt.size >> tt.rest;
            vt.push_back(tt);

            if(tt.size*2 > k)
                sz_marker = 1;
        }

        if(sz_marker == 1)
        {
            v.push_back(-1);
            continue;
        }
        else
        {
            //v.push_back();
        }


    }


    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        if(v[l] == -1)
        {
            cout << "impossible"  << endl;
            continue;
        }
        cout << v[l];
        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    return 0;
}