#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <stdlib.h>

using namespace std::chrono;
using namespace std;

//partially adapted from http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
// and http://www.mathopenref.com/coordpolygonarea.html
typedef struct tubeParams
{
    int a, b, k;
    double x;
} cords;

typedef struct vsol
{
    int n;
    int m;
    vector<tubeParams> vin;
} vsol;


vector<long double> v;

long double PI = acosl(-1.0L);

double calcRectArea(int cs)
{
    double area = 0.0;
    int tres = 0;


    area = (double) abs(area) / 2;

    return area;
}

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);
    cin.tie();

    int t = 1;

    cin >> t;
    cin.ignore();
    vector<vsol> vinpt;

    for (int i = 1; i <= t; ++i)
    {
        vsol vs;
        tubeParams cd;

        vs.vin.clear();

        cin >> vs.n >> vs.m;

        for (int j = 0; j < vs.m; ++j)
        {
            cin >> cd.a >> cd.b >> cd.k >> cd.x;

            vs.vin.push_back(cd);
        }
        //vinpt.push_back(vs);

        long double area = 999999999.0;
        long double ta = 0.0;
        for (int l = 0; l < vs.m; ++l)
        {
            //calc area of a circle:
            if (vs.vin[l].k == 0)
            {
                ta = PI * pow(vs.vin[l].x, 2);
            }
                //area of a regular polygon:
            else
            {
                if (vs.vin[l].k == 3)
                {
                    ta = sqrt(pow(vs.vin[l].x, 2) - pow(vs.vin[l].x / 2, 2));
                    ta = 0.5 * ta * vs.vin[l].x;
                }
                else
                {
                    ta = 0.25 * pow(vs.vin[l].x, 2) * vs.vin[l].k
                         * pow(tan(PI / vs.vin[l].k), -1);
                }

            }

            if (ta < area)
            {
                area = ta;
            }

        }

        v.push_back(area);

    }

    cout << std::fixed;
    cout.precision(9);
    //cout << PI;
    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        if (v[l] <= 0.0)
        {
            cout << "impossible";
        }
        else
        {
            cout << v[l];
        }

        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    return 0;
}