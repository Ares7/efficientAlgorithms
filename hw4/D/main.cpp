#include <iostream>
#include <list>
#include <queue>

using namespace std;

typedef struct OutTime
{
    long long int hours;
    string min;
}
        OutTime;

vector<OutTime> v;

class Graph
{

    long long int N;
    //first: node, second its weight
public:
    list<pair<long long int, long long int> > *neigb;
    list<pair<long long int, long long int> >::iterator i;


public:

    typedef struct shops
    {
        long long int node;
        long long int time;
    } shops;


    vector<shops> shopList;

    long long int posA;
    long long int posB;

    long long int isImpShop = 0;

    long long int impCase = 0;


    OutTime transformTime(long long int numMinutes)
    {
        OutTime ot;
        ot.hours = numMinutes / 60;
        if (numMinutes % 60 == 0)
        {
            ot.min = "00";
        }
        else if (numMinutes >= 1 && numMinutes <= 9)
        {
            ot.min = "0" + to_string(numMinutes % 60);
        }
        else
        {
            ot.min = to_string(numMinutes % 60);
        }


        return ot;
    }

    long long int FillGraph()
    {
        long long int n, m, s, a, b;
        cin >> n >> m >> s >> a >> b;
        OutTime ot;
        shops sps;

        list<pair<long long int, long long int> >::iterator xptr;
        list<pair<long long int, long long int> >::iterator yptr;


        this->N = n;
        this->posA = a - 1;
        this->posB = b - 1;
        neigb = new list<pair<long long int, long long int> >[n];

        for (long long int i = 0; i < m; ++i)
        {

            long long int x, y, z;
            cin >> x >> y >> z;
            //if not self-looped
            if (x != y)
            {
                //if we add additional edge with smaller or bigger weight value.
                neigb[x - 1].push_back(make_pair(y - 1, z));
                neigb[y - 1].push_back(make_pair(x - 1, z));
            }

        }

        long long int si = 0, wi = 0;
        for (long long int j = 0; j < s; ++j)
        {
            cin >> si >> wi;

            sps.node = si-1;
            sps.time = wi;

            shopList.push_back(sps);

        }

        if (s == 0)
        {
            //the case is completely screwed.
            ot.hours = -2;
            v.push_back(ot);
            isImpShop = 1;
            return -1;
        }
        if (m == 0 && a != b)
        {
            //the case is completely screwed.
            ot.hours = -2;
            v.push_back(ot);
            isImpShop = 1;
            return -1;
        }

        return 0;
    }


    void Dijkstra(long long int fromPt, long long int vst[10000], long long int dst[], long long int prd[])
    {
        /*
       template<
            class T,
            class Container = std::vector<T>,
            class Compare = std::less<typename Container::value_type>
            > class priority_queue;

             Weight is used used as first item  of pair
            as first item is by default used to compare
            two pairs. the 2nd item is the node to which the dist applies.
         */

        //vertex, weight
        priority_queue<pair<long long int, long long int>, vector<pair<long long int, long long int> > > pq;

        vst[fromPt] = 0;

        dst[fromPt] = 0;
        prd[fromPt] = -99;

        //1rg: node 0 with 2nd arg: weight = 0
        pq.push(make_pair(fromPt, 0));

        while (!pq.empty())
        {
            long long int u = pq.top().first;
            pq.pop();


            for (i = neigb[u].begin(); i != neigb[u].end(); ++i)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                long long int v = (*i).first;
                long long int weight = (*i).second;


                if (dst[v] > (dst[u] + weight))
                {
                    vst[v] = 0;
                }
                if (vst[v] == 0)
                {
                    if (dst[v] > dst[u] + weight)
                    {
                        dst[v] = dst[u] + weight;

                        // re-check all nodes that have incoming edge
                        // from the updated node to update their distances.

                        pq.push(make_pair(v, dst[v]));
                        prd[v] = u;
                        vst[v] = 0;

                    }

                    else
                    {
                        vst[v] = 1;
                    }

                }


            }
        }


    }
};


int main()
{

    std::ios::sync_with_stdio(false);

    long long int t = 1;

    cin >> t;
    cin.ignore();

    //Read input data
    for (long long int k = 0; k < t; ++k)
    {

        Graph gr;
        OutTime out1;
        gr.shopList.clear();

        //graph was filled successfully
        if (gr.FillGraph() == 0)
        {
            long long int visitedA[10000], distA[10000], predA[10000];
            long long int visitedB[10000], distB[10000], predB[10000];
            fill(visitedA, visitedA + 10000, 0);
            fill(distA, distA + 10000, 9223372036854775807);
            fill(predA, predA + 10000, -99);

            fill(visitedB, visitedB + 10000, 0);
            fill(distB, distB + 10000, 9223372036854775807);
            fill(predB, predB + 10000, -99);


            gr.Dijkstra(gr.posA, visitedA, distA, predA);
            gr.Dijkstra(gr.posB, visitedB, distB, predB);

            long long int minDist = 9223372036854775807;
            for (long long int i = 0; i < gr.shopList.size(); ++i)
            {
                long long int dA = distA[gr.shopList[i].node];
                long long int dB = distB[gr.shopList[i].node];
                long long int dt  = gr.shopList[i].time;
                if((dA >= 9223372036854775807 || dB >= 9223372036854775807))
                {
                    continue;
                }
                else if (minDist > (dA + dB + dt))
                {
                    minDist  = dA + dB + dt;
                }

            }

            if (minDist >= 9223372036854775807)
            {
                //gr.impCase = 0;
                out1.hours = -1;
                v.push_back(out1);
            }
            else
            {
                out1 = gr.transformTime(minDist);
                v.push_back(out1);
            }



        }


    }


    cout << endl;

    for (long long int j = 0; j < t; ++j)
    {

        cout << "Case #" << j + 1 << ": ";

        if (v[j].hours == -1 || v[j].hours == -2)
        {
            cout << "impossible";
        }
        else
        {
            cout << v[j].hours << ":" << v[j].min;
        }
        cout << endl;
    }
    return 0;
}
