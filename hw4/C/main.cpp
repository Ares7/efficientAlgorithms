#include <iostream>
#include <list>
#include <queue>
#include <array>

using namespace std;


class Graph
{

    int N;
    //first: node, second its weight
public:
    list<pair<int, int> > *neigb;
    list<pair<int, int> >::iterator i;

    //first: node, second its weight
    //list<pair<int, int> > *backneigb;
    //list<pair<int, int> >::iterator j;

    typedef struct prefetch
    {
        int x;
        int w;

        int m;

        vector<int> backneigb;

    } prefetch;

    vector<prefetch> vpref;
public:

    array<int, 1000> visited;
    array<int, 1000> pred;
    array<int, 1000> dist;


    Graph(int *n)
    {
        this->N = *n;
        neigb = new list<pair<int, int> >[*n];
    }

    void FillGraph(int *n)
    {

        for (int i = 0; i < *n; ++i)
        {
            //weight, number of neighb.
            int p, s;
            int si;

            prefetch prf;
            cin >> p >> s;

            prf.x = i;
            prf.w = p;
            prf.m = s;

            if (*n == 1)
            {
                dist[0] = -prf.w;
                return;
            }

            for (int j = 0; j < s; ++j)
            {
                cin >> si;

                prf.backneigb.push_back(si - 1);

                //neigb[i].push_back(make_pair(si -1, -p));

                //backneigb[si-1].push_back(make_pair(i, 0));
            }


            vpref.push_back(prf);
        }

        // consolidate neighbours and back neigbors data
        // to build the final graph with negative weights.

        int weight = 0;
        for (int k = 0; k < *n; ++k)
        {
            //neigb[i].push_back(make_pair(si -1, -p));

            for (int j = 0; j < vpref[k].m; ++j)
            {
                int dest = vpref[k].backneigb[j];
                weight = -vpref[dest].w;

                //handling the 1st node, adding(substracting) the value
                // of its weight from the outgoing edges.
                if (k == 0)
                {
                    weight = weight - vpref[k].w;
                }

                neigb[k].push_back(make_pair(dest, weight));
            }


        }

    }

    bool operator()(pair<int, int> n1, pair<int, int> n2)
    {
        return n1.second > n2.second;
    }

    void BellmanFord()
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


        priority_queue<pair<int, int>, vector<pair<int, int> > > pq;

        visited[0] = 0;


        dist[0] = 0;
        pred[0] = -99;

        int phase = 0;

        //1rg: node 0 with 2nd arg: weight = 0
        pq.push(make_pair(0, 0));

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

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

                        pq.push(make_pair(dist[v] + weight, v));
                        pred[v] = u;
                        visited[v] = 0;
                    }
                    else
                    {
                        visited[v] = 1;
                    }

                }


            }
        }


    }
};


int main()
{

    std::ios::sync_with_stdio(false);

    int t = 1;
    int n;
    vector<int> v;

    cin >> t;
    cin.ignore();


    //

    //Read input data
    for (int k = 0; k < t; ++k)
    {

        cin >> n;
        Graph gr(&n);

        gr.visited.fill(0);
        gr.pred.fill(-99);
        gr.dist.fill(0);


        gr.FillGraph(&n);

        if (n != 1)
        {
            gr.BellmanFord();
        }

        v.push_back(-gr.dist[n - 1]);
//        for (int r = 0; r < n; ++r)
//        {
//            for (gr.i = gr.neigb[r].begin(); gr.i != gr.neigb[r].end(); ++gr.i)
//            {
//                // Get vertex label and weight of current adjacent
//                // of u.
//                int v = (*gr.i).first;
//                int weight = (*gr.i).second;
//
//                cout << v<< " " << weight<<" ";
//            }
//            cout << endl;
//        }

    }


    cout << endl;

    for (int j = 0; j < t; ++j)
    {

        cout << "Case #" << j + 1 << ": " << v[j];
        cout << endl;
    }
    return 0;
}
