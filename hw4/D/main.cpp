#include <iostream>
#include <list>
#include <queue>
#include <array>
#include <unordered_map>

using namespace std;


typedef struct OutTime
{
    int hours;
    string min;
}
OutTime;

vector<OutTime> v;

class Graph
{

    int N;
    //first: node, second its weight
public:
    list<pair<int, int> > *neigb;
    list<pair<int, int> >::iterator i;


public:

    array<int, 10000> visited;
    array<int, 10000> pred;
    array<int, 10000> dist;

    //if the node has been visited after the shop.
    array<int, 10000> shopped;

    typedef struct shops
    {
        int time;
    } shops;


    unordered_map<int, shops> shopList;

    int totalTravelTime = 999999999;
    int hasvisitedShop = 0;
    int posA;
    int posB;

    int isImpShop = 0;

    Graph()
    {

    }


    OutTime transformTime(int numMinutes)
    {
        OutTime ot;
        ot.hours = numMinutes / 60;
        if(numMinutes % 60 == 0)
        {
            ot.min = "00";
        }
        else
        {
            ot.min = to_string(numMinutes % 60);
        }


        return ot;
    }

    int FillGraph()
    {
        int n, m, s, a, b;
        cin >> n >> m >> s >> a >> b;
        OutTime ot;
        list<pair<int, int> >::iterator xptr;
        list<pair<int, int> >::iterator yptr;


        this->N = n;
        this->posA = a - 1;
        this->posB = b - 1;
        neigb = new list<pair<int, int> >[n];

        for (int i = 0; i < m; ++i)
        {

            int x, y, z;
            cin >> x >> y >> z;
            //if not self-looped
            if (x != y)
            {
                //if we add additional edge with smaller or bigger weight value.
                neigb[x - 1].push_back(make_pair(y - 1, z));
                neigb[y - 1].push_back(make_pair(x - 1, z));
            }

        }

        int si = 0, wi = 0;
        for (int j = 0; j < s; ++j)
        {
            cin >> si >> wi;

            if (shopList[si - 1].time > wi || shopList[si - 1].time == 0)
            {
                shopList[si - 1].time = wi;
            }
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


    void BellmanFord(int shopTime)
    {
        //int shopTime = 99999999;


        /*
         1. go through every node as in normal BFord.
         2. if node has a shop (shops[i] < 9999) chk if its value is
            less than the shop we have already visited. if its less,
            then assign the global value of the shop this new value.

         3. update the shop value and he dist only if the the dist
            of pred plus the prev shop value plus
            weight of the connecting edge(which one? -> every)
            is less than the current distance from the root plus current value
            of the shop.
            put the updated node int othe queue.

            once we see the shop node for the 1st time,
            we set the global val of the shop to the val of the shop
            and all subsequent node steps will eploy this value or smth more
            optimal value.

         */


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
        priority_queue<pair<int, int>, vector<pair<int, int> > > pq;

        visited[this->posA] = 0;

        dist[this->posA] = 0;
        pred[this->posA] = -99;

        int phase = 0;

        if (shopList[this->posA].time == shopTime)
        {
            //dist[this->posA] = shopTime;
            shopped[this->posA] = shopTime;
            this->hasvisitedShop = 1;
        }


        //1rg: node 0 with 2nd arg: weight = 0
        pq.push(make_pair(this->posA, 0));

        while (!pq.empty())
        {
            int u = pq.top().first;
            pq.pop();

            if (shopList[u].time == shopTime)
            {
                this->hasvisitedShop = 1;
                shopped[u] = shopTime;
            }

            for (i = neigb[u].begin(); i != neigb[u].end(); ++i)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = (*i).first;
                int weight = (*i).second;


                if (dist[v] > (dist[u] + weight))
                {
                    visited[v] = 0;
                }
                if (visited[v] == 0)
                {
                    if (dist[v] > dist[u] + weight)
                    {
                        dist[v] = dist[u] + weight;

                        // re-check all nodes that have incoming edge
                        // from the updated node to update their distances.

                        pq.push(make_pair(v, dist[v]));
                        pred[v] = u;
                        visited[v] = 0;
                        if (hasvisitedShop == 1)
                        {
                            shopped[v] = shopTime;
                        }
                    }

                    else
                    {
                        visited[v] = 1;
                    }

                }
                //visited[v] == 1 &&
                if (shopped[v] == 0 && this->hasvisitedShop == 1)
                {
                    dist[v] = 999999999;
                    pq.push(make_pair(u, dist[u]));
                    visited[v] = 0;
                }


            }
        }


    }
};


int main()
{

    std::ios::sync_with_stdio(false);

    int t = 1;

    cin >> t;
    cin.ignore();

    //Read input data
    for (int k = 0; k < t; ++k)
    {

        Graph gr;
        OutTime out1;
        gr.shopList.clear();
        gr.totalTravelTime = 999999999;

        //graph was filled successfully
        if (gr.FillGraph() == 0)
        {
            int numShops = 0;
            //goes through values, not keys
            for (auto i: gr.shopList)
            {
                numShops++;
                gr.shopped.fill(0);
                gr.visited.fill(0);
                gr.pred.fill(-99);
                gr.dist.fill(999999999);
                gr.hasvisitedShop = 0;
                gr.BellmanFord(i.second.time);


                if (gr.isImpShop == 0)
                {
                    if (gr.totalTravelTime > gr.shopped[gr.posB] + gr.dist[gr.posB] && gr.hasvisitedShop == 1)
                    {
                        gr.totalTravelTime = gr.shopped[gr.posB] + gr.dist[gr.posB];
                    }

                }
                else
                {
                    gr.isImpShop = 0;
                    continue;
                }

            }

            //perform time transform.
            if (gr.hasvisitedShop == 0 && numShops == gr.shopList.size())
            {
                out1.hours = -1;
                v.push_back(out1);
            }
            else
            {
                out1 = gr.transformTime(gr.totalTravelTime);
                v.push_back(out1);
            }
        }


    }


    cout << endl;

    for (int j = 0; j < t; ++j)
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
