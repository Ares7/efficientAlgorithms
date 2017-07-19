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
// and http://www.mathopenref.com/coordpolygonarea.html
typedef struct cords
{
    int x, y, z, t;
} cords;


typedef struct vsol
{
    int n;
    vector<cords> vin;
} vsol;

vector<vsol> v;


vector<double> vres;


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


double calcArea(vector<Point> pt)
{
    double area = 0.0;
    double tres = 0.0;
    double ta = 0.0;
    double tb = 0.0;
    double tc = 0.0;

    if (pt.size() >= 4)
    {
        for (int i = 0; i < pt.size() - 1; ++i)
        {
            tres = (double) (pt[i].x * pt[i + 1].y - pt[i].y * pt[i + 1].x);
            area += tres;
        }
        tres = (double) (pt[pt.size() - 1].x * pt[0].y - pt[pt.size() - 1].y * pt[0].x);
        area += tres;
        area = abs(area) / 2;
    }
    else
    {
        ta = pt[0].x * (pt[1].y - pt[2].y);
        tb = pt[1].x * (pt[2].y - pt[0].y);
        tc = pt[2].x * (pt[0].y - pt[1].y);
        area = abs((ta + tb + tc) / 2);
    }


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
        cords cd;
        Point points;

        vs.vin.clear();
        vpts.clear();

        cin >> vs.n;

        for (int j = 0; j < vs.n; ++j)
        {
            cin >> cd.x >> cd.y;

            vs.vin.push_back(cd);
        }
        vinpt.push_back(vs);

        int ix = 0;

        while (ix < vs.n)
        {
            points.x = vs.vin[ix].x;
            points.y = vs.vin[ix].y;
            ix++;
            vpts.push_back(points);
        }


        vres.push_back(calcArea(convex_hull(vpts)) * 2);


    }

    cout << std::fixed;
    for (int l = 0; l < vres.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout << vres[l];
        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    return 0;
}



//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <chrono>
//#include <cmath>
//#include <sstream>
//#include <unordered_map>
//#include <stack>
//#include <stdlib.h>
//
//using namespace std::chrono;
//using namespace std;
//
////partially adapted from http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
//// and http://www.mathopenref.com/coordpolygonarea.html
//typedef struct cords
//{
//    int x, y, z, t;
//} cords;
//
//
//typedef struct vsol
//{
//    int n;
//    vector<cords> vin;
//} vsol;
//
//
//struct Point
//{
//    int x, y;
//};
//
//vector<vsol> v;
//
//
//vector<double> vres;
//// A globle point needed for  sorting points with reference
//// to  the first point Used in compare function of qsort()
//Point p0;
//
//
//// A utility function to find next to top in a stack
//Point nextToTop(stack<Point> &S)
//{
//    Point p = S.top();
//    S.pop();
//    Point res = S.top();
//    S.push(p);
//    return res;
//}
//
//// A utility function to swap two points
//void swap(Point &p1, Point &p2)
//{
//    Point temp = p1;
//    p1 = p2;
//    p2 = temp;
//}
//
//// A utility function to return square of distance
//// between p1 and p2
//int distSq(Point p1, Point p2)
//{
//    return (p1.x - p2.x)*(p1.x - p2.x) +
//           (p1.y - p2.y)*(p1.y - p2.y);
//}
//
//// To find orientation of ordered triplet (p, q, r).
//// The function returns following values
//// 0 --> p, q and r are colinear
//// 1 --> Clockwise
//// 2 --> Counterclockwise
//int orientation(Point p, Point q, Point r)
//{
//    int val = (q.y - p.y) * (r.x - q.x) -
//              (q.x - p.x) * (r.y - q.y);
//
//    if (val == 0) return 0;  // colinear
//    return (val > 0)? 1: 2; // clock or counterclock wise
//}
//
//// A function used by library function qsort() to sort an array of
//// points with respect to the first point
//int compare(const void *vp1, const void *vp2)
//{
//    Point *p1 = (Point *)vp1;
//    Point *p2 = (Point *)vp2;
//
//    // Find orientation
//    int o = orientation(p0, *p1, *p2);
//    if (o == 0)
//        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
//
//    return (o == 2)? -1: 1;
//}
//
//// Prints convex hull of a set of n points.
//void convexHull(Point points[], int n)
//{
//    // Find the bottommost point
//    int ymin = points[0].y, min = 0;
//    for (int i = 1; i < n; i++)
//    {
//        int y = points[i].y;
//
//        // Pick the bottom-most or chose the left
//        // most point in case of tie
//        if ((y < ymin) || (ymin == y &&
//                           points[i].x < points[min].x))
//            ymin = points[i].y, min = i;
//    }
//
//    // Place the bottom-most point at first position
//    swap(points[0], points[min]);
//
//    // Sort n-1 points with respect to the first point.
//    // A point p1 comes before p2 in sorted ouput if p2
//    // has larger polar angle (in counterclockwise
//    // direction) than p1
//    p0 = points[0];
//    qsort(&points[1], n-1, sizeof(Point), compare);
//
//    // If two or more points make same angle with p0,
//    // Remove all but the one that is farthest from p0
//    // Remember that, in above sorting, our criteria was
//    // to keep the farthest point at the end when more than
//    // one points have same angle.
//    int m = 1; // Initialize size of modified array
//    for (int i=1; i<n; i++)
//    {
//        // Keep removing i while angle of i and i+1 is same
//        // with respect to p0
//        while (i < n-1 && orientation(p0, points[i],
//                                      points[i+1]) == 0)
//            i++;
//
//
//        points[m] = points[i];
//        m++;  // Update size of modified array
//    }
//
//    // If modified array of points has less than 3 points,
//    // convex hull is not possible
//    if (m < 3) return;
//
//    // Create an empty stack and push first three points
//    // to it.
//    stack<Point> S;
//    S.push(points[0]);
//    S.push(points[1]);
//    S.push(points[2]);
//
//    // Process remaining n-3 points
//    for (int i = 3; i < m; i++)
//    {
//        // Keep removing top while the angle formed by
//        // points next-to-top, top, and points[i] makes
//        // a non-left turn
//        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
//            S.pop();
//        S.push(points[i]);
//    }
//
//    vsol vs;
//    cords cor;
//
//    int ix =0;
//    // Now stack has the output points, print contents of stack
//    while (!S.empty())
//    {
//        ix++;
//        Point p = S.top();
//        cor.x = p.x;
//        cor.y = p.y;
//        vs.vin.push_back(cor);
//        S.pop();
//    }
//    vs.n  = ix;
//    //sort(vs.vin.begin(), vs.vin.end(), compareByID);
//
//    //put results to the final vector:
//    v.push_back(vs);
//}
//
//
//double calcArea(int cs)
//{
//    double area = 0.0;
//    double tres = 0;
//
//    for (int i = 0; i < v[cs].n -1; ++i)
//    {
//        tres = (double)(v[cs].vin[i].x * v[cs].vin[i+1].y - v[cs].vin[i].y * v[cs].vin[i+1].x);
//        area+=tres;
//    }
//    tres = (double)(v[cs].vin[v[cs].n -1].x * v[cs].vin[0].y - v[cs].vin[v[cs].n -1].y * v[cs].vin[0].x);
//    area+=tres;
//    area = abs(area)/2;
//
//    return area;
//}
//
//int main()
//{
//    high_resolution_clock::time_point t1 = high_resolution_clock::now();
//
//    std::ios::sync_with_stdio(false);
//    cin.tie();
//
//    int t = 1;
//
//    cin >> t;
//    cin.ignore();
//    vector<vsol> vinpt;
//
//    for (int i = 1; i <= t; ++i)
//    {
//        vsol vs;
//        cords cd;
//        Point points[10000];
//
//        vs.vin.clear();
//
//        cin >> vs.n;
//
//        for (int j = 0; j < vs.n; ++j)
//        {
//            cin >> cd.x >> cd.y;
//
//            vs.vin.push_back(cd);
//        }
//        vinpt.push_back(vs);
//
//        int ix = 0;
//
//        while(ix <= vs.n)
//        {
//            points[ix].x = vs.vin[ix].x;
//            points[ix].y = vs.vin[ix].y;
//            ix++;
//        }
//
//        //run Convex Hull calculation.
//        convexHull(points, vs.n);
//
//        if(v.size()>0)
//        {
//            //calc the volume by doubling the Area for the given case:
//            vres.push_back(calcArea(i-1) * 2);
//        }
//        else
//        {
//            vres.push_back(0);
//        }
//
//
//
//    }
//
//    cout << std::fixed;
//    for (int l = 0; l < vres.size(); ++l)
//    {
//        cout << "Case #" << l + 1 << ": ";
//        cout<< vres[l];
//        cout << endl;
//    }
//
//    high_resolution_clock::time_point t2 = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(t2 - t1).count();
//    //cout << duration;
//    return 0;
//}