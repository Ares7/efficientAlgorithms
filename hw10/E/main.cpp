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
typedef struct cords
{
    int x, y, z, t;
} cords;


typedef struct vsol
{
    int n;
    vector<cords> vin;
} vsol;


struct Point
{
    int x, y;
};

vector<vsol> v;


vector<double> vres;
// A globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;


// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
           (p1.y - p2.y)*(p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{
    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
                           points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at first position
    swap(points[0], points[min]);

    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted ouput if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);

    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i=1; i<n; i++)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < n-1 && orientation(p0, points[i],
                                      points[i+1]) == 0)
            i++;


        points[m] = points[i];
        m++;  // Update size of modified array
    }

    // If modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3) return;

    // Create an empty stack and push first three points
    // to it.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++)
    {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    vsol vs;
    cords cor;

    int ix =0;
    // Now stack has the output points, print contents of stack
    while (!S.empty())
    {
        ix++;
        Point p = S.top();
        cor.x = p.x;
        cor.y = p.y;
        vs.vin.push_back(cor);
        S.pop();
    }
    vs.n  = ix;
    //sort(vs.vin.begin(), vs.vin.end(), compareByID);

    //put results to the final vector:
    v.push_back(vs);
}


double calcArea(int cs)
{
    double area = 0.0;
    int tres = 0;

    for (int i = 0; i < v[cs].n -1; ++i)
    {
        tres = (double)(v[cs].vin[i].x * v[cs].vin[i+1].y - v[cs].vin[i].y * v[cs].vin[i+1].x);
        area+=tres;
    }
    tres = (double)(v[cs].vin[v[cs].n -1].x * v[cs].vin[0].y - v[cs].vin[v[cs].n -1].y * v[cs].vin[0].x);
    area+=tres;
    area = (double)abs(area)/2;

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
        Point points[1000];

        vs.vin.clear();

        cin >> vs.n;

        for (int j = 0; j < vs.n; ++j)
        {
            cin >> cd.x >> cd.y;

            vs.vin.push_back(cd);
        }
        vinpt.push_back(vs);

        int ix = 0;
        //run Convex Hull calculation.
        while(ix <= vs.n)
        {
            points[ix].x = vs.vin[ix].x;
            points[ix].y = vs.vin[ix].y;
            ix++;
        }
        convexHull(points, vs.n);

        //calc the volume by doubling the Area for the given case:
        vres.push_back(calcArea(i-1) * 2);


    }

    cout << std::fixed;
    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout<< vres[l];
        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    return 0;
}