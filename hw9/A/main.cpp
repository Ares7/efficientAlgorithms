#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std::chrono;


using namespace std;

typedef struct vsol
{
    int n, c;
    int* marks;
    vector<int> vin;
    vector<int> vout;
} vsol;

vector<vsol> v;

int optimalSum(vsol vs, int ix)
{
    int sum = 0;
    while (sum <vs.c  && ix >= 0)
    {
        if(sum+vs.vin[ix] <= vs.c)
        {
            sum+=vs.vin[ix];
            vs.vout.push_back(vs.vin[ix]);
            vs.marks[ix] +=1;
        }
        else
        {
            ix--;
            continue;
        }

    }

    return sum;
}

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);
//
    int t = 1;


    cin >> t;
    cin.ignore();
    int coin, sum, ix;



    for (int i = 1; i <= t; ++i)
    {
        vsol vs;
        vs.marks = new int [100];

        cin >> vs.n >> vs.c;
        vs.vin.clear();
        vs.vout.clear();
        memset(vs.marks, 0, sizeof(int));
        sum  = 0;

        for (int j = 0; j < vs.n ; ++j)
        {
            cin >> coin;
            vs.vin.push_back(coin);
        }

        optimalSum(vs, vs.n-1);

        v.push_back(vs);
        delete[] vs.marks;

    }

    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        for (int i = 0; i < v[l].n; ++i)
        {
            cout << v[l].marks[i] << " ";

        }

        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    return 0;
}