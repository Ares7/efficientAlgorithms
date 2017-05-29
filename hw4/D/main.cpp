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
    }shops;


    unordered_map<int, shops> shopList;

    int globalshopTime = INT_MAX;
    int hasvisitedShop = 0;
    int posA;
    int posB;


    Graph()
    {

    }


    OutTime transformTime(int numMinutes)
    {
        OutTime ot;
        if ((numMinutes / 60) == 1)
        {
            printf("%01d hour", numMinutes / 60);
        }
        else
        {
            printf("%01d hours", numMinutes / 60);
        }

        if ((numMinutes % 60) == 1)
        {
            printf(" %01d minute\n", numMinutes % 60);
        }
        else
        {
            printf(" %01d minutes\n", numMinutes % 60);
        }

        return ot;
    }

    void FillGraph()
    {
        int n, m, s, a, b;
        cin >> n >> m >> s >> a >> b;


        if (s == 0)
        {
            OutTime ot;
            //the case is completely screwed.
            ot.hours = -2;
            v.push_back(ot);
            return;
        }
        this->N = n;
        this->posA = a - 1;
        this->posB = b - 1;
        neigb = new list<pair<int, int> >[n];

        for (int i = 0; i < m; ++i)
        {

            int x, y, z;
            cin >> x >> y >> z;

            if (x != y)
            {
                neigb[x-1].push_back(make_pair(y-1, z));
                neigb[y-1].push_back(make_pair(x-1, z));
            }

        }

        int si = 0, wi = 0;
        for (int j = 0; j < s; ++j)
        {
            cin >> si >> wi;

            if (shopList[si-1].time > wi || shopList[si-1].time== 0)
            {
                shopList[si-1].time = wi;
            }
        }

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

        //TODO: DEFINE CORRECT START AND END
        visited[this->posA] = 0;

        dist[this->posA] = 0;
        pred[this->posA] = -99;

        int phase = 0;

        if(shopList[this->posA].time == shopTime)
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

            if(shopList[u].time > 0 && shopList[u].time == shopTime)
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


                if (dist[v] > (dist[u] + weight ))
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
                        shopped[v] = shopTime;
                    }

                    else
                    {
                        visited[v] = 1;
                    }

                }
                else if(visited[v] == 1 && shopped[v]==0 && this->hasvisitedShop == 1)
                {
                    pq.push(make_pair(v, dist[v]));
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


    //

    //Read input data
    for (int k = 0; k < t; ++k)
    {

        Graph gr;
        OutTime out1;

        gr.visited.fill(0);
        gr.pred.fill(-99);
        gr.dist.fill(INT_MAX);
        gr.shopped.fill(0);

        gr.FillGraph();

        //goes through values, not keys
        for (auto i: gr.shopList)
        {
            gr.BellmanFord(i.second.time);

            //TODO shoped B still holds val of 20 after
            // node with shop of 15 went though.
            if (gr.globalshopTime > gr.shopped[gr.posB] && gr.hasvisitedShop == 1)
            {
                gr.globalshopTime = gr.shopped[gr.posB];
            }
            else if(gr.hasvisitedShop == 0)
            {
                out1.hours = -1;
                v.push_back(out1);
            }
        }

        //perform time tranform.

        OutTime ot;
        ot = gr.transformTime(gr.globalshopTime);

        v.push_back(ot);


    }


    cout << endl;

    for (int j = 0; j < t; ++j)
    {

        cout << "Case #" << j + 1 << ": ";
        if (v[j].hours == -1)
        {
            cout << "impossible";
        }
        else
        {
            cout << "correct time";
        }
        cout << endl;
    }
    return 0;
}
