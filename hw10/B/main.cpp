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

//partially adapted from https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C.2B.2B

typedef struct cords
{
    int x, y, z, t;
} cords;



typedef double coord_t;         // coordinate type
typedef double coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2

struct Point
{
    coord_t x, y;

    bool operator<(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

vector<Point> vpts;

typedef struct vsol
{
    int n;
    vector<Point> vin;
} vsol;

vector<vsol> v;

bool compareByID(const Point &a, const Point &b) {
    return (a.x < b.x) || (a.x == b.x  && a.y < b.y);
}

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P)
{
    int n = P.size(), k = 0;
    if (n == 1)
    { return P; }
    vector<Point> H(2 * n);

    // Sort points lexicographically
    sort(P.begin(), P.end());

    // Build lower hull
    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--)
    {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    H.resize(k - 1);
    return H;
}


int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);
    cin.tie();

    int t = 1;

    cin >> t;
    cin.ignore();

    for (int i = 1; i <= t; ++i)
    {
        vsol vs;
        cords cd;
        Point points;

        vpts.clear();

        cin >> vs.n;

        for (int j = 0; j < vs.n; ++j)
        {
            cin >> cd.x >> cd.y >> cd.z >> cd.t;

            points.x = cd.x;
            points.y = cd.y;

            vpts.push_back(points);
        }

        //run Convex Hull calculation.
        vs.vin = convex_hull(vpts);
        sort(vs.vin.begin(), vs.vin.end(), compareByID);

        v.push_back(vs);

    }

    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout << endl;
        cout<< v[l].vin.size();
        cout << endl;
        for (int i = 0; i < v[l].vin.size(); ++i)
        {
            cout<< v[l].vin[i].x << " " << v[l].vin[i].y;
            cout << endl;
        }
        //cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    return 0;
}