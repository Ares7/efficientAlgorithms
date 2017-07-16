#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <sstream>
#include <unordered_map>

using namespace std::chrono;
using namespace std;

//partially adapted from geeksforgeeks.com
// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

struct SimpleHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return p.first ^ p.second;
    }
};

typedef struct cords
{
    int x1, y1, x2, y2;
} cords;

typedef struct vsol
{
    int xim, yim , n;

    vector<cords> vin;
} vsol;

vector<string> v;
unordered_map< pair<int, int>, int, SimpleHash> visp;


struct Point
{
    int x;
    int y;
};


// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
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

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}

// Returns true if the point p lies inside the polygon[] with n vertices
bool isInside(Point polygon[], int n, Point p)
{
    // There must be at least 3 vertices in polygon[]
    if (n < 3)  return false;

    // Create a point for line segment from p to infinite
    Point extreme = {INF-2, INF-1};

    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
        int next = (i+2)%n;

        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(polygon[i], polygon[i+1], p, extreme) )
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(polygon[i], p, polygon[i+1]) == 0)
                return onSegment(polygon[i], p, polygon[i+1]);

            if(visp[make_pair(polygon[i].x, polygon[i].y)] != 1 && visp[make_pair(polygon[i+1].x, polygon[i+1].y)] != 1)
            {
                visp[make_pair(polygon[i].x, polygon[i].y)] = 1;
                visp[make_pair(polygon[i+1].x, polygon[i+1].y)] = 1;

                count++;
            }

        }
        i = next;
    } while (i != 0);

    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
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

        cin >> vs.xim >> vs.yim >> vs.n;

        Point polygon1[2000];
        int n = vs.n*2;

        cin.ignore();
        string x1, y1, x2, y2;
        int ix = 1, ixP = 0;
        while(ix <= vs.n)
        {
            std::getline(cin, x1, ' ');
            std::getline(cin, y1, ' ');
            std::getline(cin, x2, ' ');
            std::getline(cin, y2, '\n');
            cd.x1 = stoi(x1);
            cd.y1 = stoi(y1);

            cd.x2 = stoi(x2);
            cd.y2 = stoi(y2);

            ix++;

            vs.vin.push_back(cd);


            polygon1[ixP].x = cd.x1;
            polygon1[ixP].y = cd.y1;

            polygon1[ixP+1].x = cd.x2;
            polygon1[ixP+1].y = cd.y2;

            ixP+=2;

        }

        vinpt.push_back(vs);


        Point p = {vs.xim , vs.yim};
        isInside(polygon1, n, p)? v.push_back("jackpot"): v.push_back("too bad");


    }

    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": " << v[l];
        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    return 0;
}