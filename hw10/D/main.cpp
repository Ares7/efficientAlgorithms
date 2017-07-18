#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <stdlib.h>
#include <list>

using namespace std::chrono;
using namespace std;

//partially adapted from http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/, stanfordacm
// and http://www.mathopenref.com/coordpolygonarea.html
typedef struct tubeParams
{
    int a, b, k;
    long double x;

    long double weight;
} cords;

typedef struct vsol
{
    int n;
    int m;
    vector<tubeParams> vin;
} vsol;


vector<long double> v;

long double PI = acosl(-1.0L);

list<pair<int, int> > *neigb;
list<pair<int, int> >::iterator i;




void calcRectArea(vsol &vs)
{
    long double area = 0.0;
    for (int l = 0; l < vs.m; ++l)
    {
        //calc area of a circle:
        if (vs.vin[l].k == 0)
        {
            area = PI * pow(vs.vin[l].x, 2);
        }
            //area of a regular polygon:
        else
        {
            if (vs.vin[l].k == 3)
            {
                area = 0.5 * sqrt(pow(vs.vin[l].x, 2) - pow(vs.vin[l].x / 2, 2))
                       * vs.vin[l].x;
            }
            else
            {
                area = 0.25 * pow(vs.vin[l].x, 2) * vs.vin[l].k
                       * pow(tan(PI / vs.vin[l].k), -1);
            }

        }

        vs.vin[l].weight = area;

    }

}


typedef vector<long double> VI;
typedef vector<VI> VVI;


struct MaxFlow
{
    int N;
    //int M;
    int posA;
    int posB;


    VVI cap, flow;
    VI dad, Q;

    MaxFlow(int N) :
            N(N), cap(N, VI(N)), flow(N, VI(N)), dad(N), Q(N)
    {
        this->posA = 0;
        this->posB = N - 1;
        //this->M = M;
    }

    void AddEdge(int from, int to, long double cap)
    {
        this->cap[from][to] += cap;
    }

    int FillGraph(vsol &vs)
    {

        for (int i = 0; i < vs.m; ++i)
        {
            this->AddEdge(vs.vin[i].a - 1, vs.vin[i].b - 1, vs.vin[i].weight);
            this->AddEdge(vs.vin[i].b - 1, vs.vin[i].a - 1, vs.vin[i].weight);

        }

        return 0;
    }

    long double BlockingFlow(int s, int t)
    {
        fill(dad.begin(), dad.end(), -1);
        dad[s] = -2;

        int head = 0, tail = 0;
        Q[tail++] = s;
        while (head < tail)
        {
            int x = Q[head++];
            for (int i = 0; i < N; i++)
            {
                if (dad[i] == -1 && cap[x][i] - flow[x][i] > 0)
                {
                    dad[i] = x;
                    Q[tail++] = i;
                }
            }
        }

        if (dad[t] == -1)
        { return 0; }

        long double  totflow = 0;
        for (int i = 0; i < N; i++)
        {
            if (dad[i] == -1)
            { continue; }
            long double amt = cap[i][t] - flow[i][t];
            for (int j = i; amt && j != s; j = dad[j])
            {
                //amt = min(amt, cap[dad[j]][j] - flow[dad[j]][j]);
                if(amt > cap[dad[j]][j] - flow[dad[j]][j])
                {
                    amt = cap[dad[j]][j] - flow[dad[j]][j];
                }
            }
            if (amt == 0)
            { continue; }
            flow[i][t] += amt;
            flow[t][i] -= amt;
            for (int j = i; j != s; j = dad[j])
            {
                flow[dad[j]][j] += amt;
                flow[j][dad[j]] -= amt;
            }
            totflow += amt;
        }

        return totflow;
    }

    long double GetMaxFlow(int source, int sink)
    {
        long double totflow = 0;
        while (long double  flow = BlockingFlow(source, sink))
            totflow += flow;
        return totflow;
    }



};

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

        calcRectArea(vs);

        MaxFlow mf(vs.n);

        mf.FillGraph(vs);

        v.push_back(mf.GetMaxFlow(0, vs.n-1));

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