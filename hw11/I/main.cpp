#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <chrono>

//partially based on https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
using namespace std::chrono;
using namespace std;

#define EPS 0.000001

#define INF 9999999999999999;

typedef struct points
{
    int num;
    double x, y;
} points;

vector<points> vinter;

typedef struct lines
{
    double x1, y1, x2, y2;
} lines;

struct cases
{
    int n, k;
    vector<lines> vl;
};


class T;

inline bool ptsAreEqual(points *pt1, points *pt2)
{
    return fabs(pt1->x - pt2->x) < EPS && fabs(pt1->y - pt2->y) < EPS;
}

// To find orientation of ordered triplet (a, b, c).
// The function returns following values
// 0 --> a, b and c are collinear
// 1 --> Clockwise        (Right of line formed by the segment)
// 2 --> Counterclockwise (Left of line formed by the segment)
int orientation(points a, points b, points c)
{
    double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (fabs(val) < EPS)
    { return 0; }  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Tests whether or not a point c is on the segment [a, b]
bool pointOnLine(points a, points b, points c)
{

    bool is_collinear = orientation(a, b, c);

    if (is_collinear == 0)
    {
        if (min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x))
        {
            if (min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y))
            {
                return true;
            }
            else
            { return false; }
        }
        else
        { return false; }
    }
    else
    { return false; }

}

// Test if two line segments [p1, p2] & [p3, p4] intersect
bool doIntersect(points p1, points p2, points p3, points p4)
{

    // find orientations
    int o1 = orientation(p1, p2, p3);
    int o2 = orientation(p1, p2, p4);
    int o3 = orientation(p3, p4, p1);
    int o4 = orientation(p3, p4, p2);

    // General case
    if (o1 != o2 && o3 != o4)
    { return true; }

    // Collinear special cases
    if (o1 == 0 && pointOnLine(p1, p2, p3))
    { return true; }
    if (o2 == 0 && pointOnLine(p1, p2, p4))
    { return true; }
    if (o3 == 0 && pointOnLine(p3, p4, p1))
    { return true; }
    if (o4 == 0 && pointOnLine(p3, p4, p2))
    { return true; }

    return false;
}

/*
 * Returns the points that the two segments have in common
 * Returns 0 - No points in common
 *         1 - One point in common  (stored in pt1)
 *         2 - Two points in common (stored in pt2)
 *         3 - Both segments are actually the same point
 */
int segmentCommonEndpoints(points *p1, points *p2, points *p3, points *p4, points *pt1, points *pt2)
{

    int count = 0;

    // All points are the same
    if (ptsAreEqual(p1, p2) && ptsAreEqual(p2, p3) && ptsAreEqual(p3, p4))
    {
        *pt1 = *p1;
        pt2 = nullptr;
        return 3;
    }
    else
    {
        if (ptsAreEqual(p1, p3))
        {
            *pt1 = *p1;
            count++;
            if (ptsAreEqual(p2, p4))
            {
                *pt2 = *p2;
                count++;
            }
        }
        else if (ptsAreEqual(p1, p4))
        {
            *pt1 = *p1;
            count++;
            if (ptsAreEqual(p2, p3))
            {
                *pt2 = *p2;
                count++;
            }
        }
        else if (ptsAreEqual(p2, p3))
        {
            *pt1 = *p2;
            count++;
            if (ptsAreEqual(p1, p4))
            {
                *pt2 = *p1;
                count++;
            }
        }
        else if (ptsAreEqual(p2, p4))
        {
            *pt1 = *p2;
            count++;
            if (ptsAreEqual(p1, p3))
            {
                *pt2 = *p1;
                count++;
            }
        }
    }

    if (count == 0)
    {
        pt1 = nullptr;
        pt2 = nullptr;
    }
    else if (count == 1)
    {
        pt2 = nullptr;
    }

    return count;
}


/*
p1 & p2 are part of the first segment and p3 & p4 are part of the second segment.
I0 and I1 are the pointers which get set when intersection point(s) are found.

Returns: 0 - No intersection
         1 - Unique intersection set in  I0
         2 - Segment intersection set in [I0, I1]
*/
int segment_segment_intersection(points p1, points p2, points p3, points p4, points *I0, points *I1)
{

    if (doIntersect(p1, p2, p3, p4))
    {

        points *pt1 = new points;
        points *pt2 = new points;
        int num_common_endpoints = segmentCommonEndpoints(&p1, &p2, &p3, &p4, pt1, pt2);
        bool singleton = ptsAreEqual(&p1, &p2) || ptsAreEqual(&p3, &p4);

        if (num_common_endpoints == 3)
        {

            *I0 = *pt1;
            I1 = nullptr;
            return 1;

        }
        else if (num_common_endpoints == 2)
        {

            *I0 = *pt1;
            *I1 = *pt2;
            return 2;

            // There is a unique singleton
        }
        else if (num_common_endpoints == 1 && singleton)
        {

            *I0 = *pt1;
            I1 = nullptr;
            return 1;

        }
        else
        {

            bool pts_form_straight_line = (orientation(p1, p2, p3) == 0) && (orientation(p1, p2, p4) == 0);

            // The intersection will be a 'subsegment' of the two segments because they overlap
            if (pts_form_straight_line)
            {

                // Segment #2 is fully enclosed in Segment #1
                if (pointOnLine(p1, p2, p3) && pointOnLine(p1, p2, p4))
                {
                    *I0 = p3;
                    *I1 = p4;
                    // Segment #1 is fully enclosed in Segment #2
                }
                else if (pointOnLine(p3, p4, p1) && pointOnLine(p3, p4, p2))
                {
                    *I0 = p1;
                    *I1 = p2;
                    // The subsegment is part of segment #1 and part of segment #2
                }
                else
                {

                    // Find 'middle points'
                    if (pointOnLine(p1, p2, p3))
                    {
                        *I0 = p3;
                    }
                    else
                    {
                        *I0 = p4;
                    }

                    if (pointOnLine(p3, p4, p1))
                    {
                        *I1 = p1;
                    }
                    else
                    {
                        *I1 = p2;
                    }
                }

                // There is actually only one middle point
                if (ptsAreEqual(I0, I1))
                {
                    I1 = nullptr;
                    return 1;
                }

                return 2;

                // Unique intersection point
            }
            else
            {

                // Segment 1 is vertical line
                if (fabs(p2.x - p1.x) < EPS)
                {

                    double m2 = (p4.y - p3.y) / (p4.x - p3.x);
                    double b2 = p3.y - m2 * p3.x;

                    I0->x = p1.x;
                    I0->y = m2 * p1.x + b2;

                    // Segment 2 is vertical line
                }
                else if (fabs(p4.x - p3.x) < EPS)
                {

                    double m1 = (p2.y - p1.y) / (p2.x - p1.x);
                    double b1 = p1.y - m1 * p1.x;

                    I0->x = p3.x;
                    I0->y = m1 * p3.x + b1;

                    // Sloped line
                }
                else
                {

                    double m1 = (p2.y - p1.y) / (p2.x - p1.x);
                    double m2 = (p4.y - p3.y) / (p4.x - p3.x);
                    double b1 = p1.y - m1 * p1.x;
                    double b2 = p3.y - m2 * p3.x;

                    I0->x = (b2 - b1) / (m1 - m2);
                    I0->y = (m1 * b2 - m2 * b1) / (m1 - m2);

                }
                I1 = nullptr;
                return 1;
            }
        }

        // No intersection exists
    }
    else
    {
        I0 = nullptr;
        I1 = nullptr;
        return 0;
    }

}

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);
//
    int t = 1;

    string sc, sfin;
    cases cs;

    lines ln;

    vector<string> v;

    cin >> t;
    cin.ignore();

    for (int i = 1; i <= t; ++i)
    {
        //fill the input DSs:
        cs.vl.clear();
        vinter.clear();
        cin >> cs.n >> cs.k;

        for (int j = 0; j < cs.n; ++j)
        {
            //read, store and process the points by pairs.
            cin >> ln.x1 >> ln.y1 >> ln.x2 >> ln.y2;
            cs.vl.push_back(ln);
        }

        points pts;
        double x, y, lenAB;
        //define coordinates of the end of every segment in focus:
        for (int k = 0; k < cs.vl.size(); ++k)
        {
            // Segment 1: prolonging the segment to make sure the laser intersects with another one.
            points p1 ;
            p1.x = cs.vl[k].x1;
            p1.y =  cs.vl[k].y1;

            lenAB = sqrt(pow(p1.x - cs.vl[k].x2, 2.0) + pow(p1.y - cs.vl[k].y2, 2.0));
            x = cs.vl[k].x2 + (cs.vl[k].x2 - cs.vl[k].x1) / lenAB * INF;
            y = cs.vl[k].y2 + (cs.vl[k].y2 - cs.vl[k].y1) / lenAB * INF;
            points p2 ;
            p2.x = x;
            p2.y = y;
            for (int j = k + 1; j < cs.vl.size(); ++j)
            {
                // Segment 2: prolonging the segment to make sure the laser intersects with another one.
                points p3 ;
                p3.x = cs.vl[j].x1;
                p3.y = cs.vl[j].y1;

                lenAB = sqrt(pow(p3.x - cs.vl[j].x2, 2.0) + pow(p3.y - cs.vl[j].y2, 2.0));
                x = cs.vl[j].x2 + (cs.vl[j].x2 - cs.vl[j].x1) / lenAB * INF;
                y = cs.vl[j].y2 + (cs.vl[j].y2 - cs.vl[j].y1) / lenAB * INF;

                points p4;
                p4.x = x;
                p4.y = y;

                points *intersection1 = new points;
                points *intersection2 = new points;

                int ret = segment_segment_intersection(p1, p2, p3, p4, intersection1, intersection2);

                //no intersection
                if (ret == 0)
                {
                    continue;
                }
                else if (ret == 1)
                {
                    // Unique Point
                    pts.x = intersection1->x;
                    pts.y = intersection1->y;

                    for (int l = 0; l < vinter.size(); ++l)
                    {
                        if (vinter[l].x == pts.x && vinter[l].y == pts.y)
                        {
                            vinter[l].num++;
                        }
                        else
                        {
                            pts.num = 2;
                        }
                    }
                    if (pts.num == 2 || vinter.size() == 0)
                    {
                        pts.num = 2;
                        vinter.push_back(pts);
                    }


                }
                else if (ret == 2)
                {

                    // Intersection is a segment from
                    // [intersection1->x, intersection1->y] to [intersection2->x, intersection2->y]

                }
                //Perform the analysis if the lines for a given case interest
                // at some points at least k times:

                //1. check every line only once, but separately for head and tail.
                //2. count # of intersections.
                //3. need to chk every lines only once bc if it doesnt create a necc amnt of
                //   intersections with all futher lines, that it will not create them
                //   in the future checks of other lines.

                delete intersection1;
                delete intersection2;
            }


        }

        //go through the list of intersention points and choose the one
        // with number of lines intersection above or eq "k".
        int mNix = 0;
        for (int l = 0; l < vinter.size(); ++l)
        {
            if (vinter[l].num > vinter[mNix].num)
            {
                mNix = l;
            }
        }
        if (vinter[mNix].num >= cs.k)
        {
            v.push_back(to_string(vinter[mNix].x) + " " + to_string(vinter[mNix].y));
        }
        else
        {
            v.push_back("no");
        }


    }


    for (int l = 0; l < t; ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout << v[l];
        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;


    return 0;
}