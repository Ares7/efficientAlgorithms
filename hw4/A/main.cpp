#include <iostream>
#include <list>
#include <queue>
#include <array>

using namespace std;


class Graph {

    int N;
    list<pair<int, int> > *neigb;
    list<pair<int, int> >::iterator i;



public:

    array<int, 1000> visited;
    array<int, 1000>  pred;
    array<int, 1000> dist;




    Graph(int *n) {
        this->N = *n;
        neigb = new list<pair<int, int> >[*n];
    }

    void FillGraph(int *n, int *m)
    {

        // read every line of the sound block
        for (int i = 0; i < *m; ++i)
        {
            int a, b, w;

            cin >> a >> b >> w;
            neigb[a - 1].push_back(make_pair(b - 1, w));
            neigb[b - 1].push_back(make_pair(a - 1, w));
        }

    }

    bool operator()(pair<int, int> n1, pair<int, int> n2)
    {
        return n1.second > n2.second;
    }

    void DijkstrsSP(int *m)
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

        visited[0] = 1;
        dist[0] = 0;
        pred[0] = -99;

        pq.push(make_pair( 0, 0));

        while(!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            for (i = neigb[u].begin(); i != neigb[u].end(); ++i)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = (*i).first;
                int weight = (*i).second;

                if(dist[v] > (dist[u] + weight))
                {
                    visited[v] = 0;
                }
                if(visited[v] == 0)
                {
                    if(dist[v] > dist[u] + weight)
                    {
                        dist[v] = dist[u] + weight;

                        // re-check all nodes that have incoming edge
                        // from the updated node to update their distances.

                        pq.push(make_pair( dist[v] + weight, v));
                        pred[v]=u;
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


int main() {

    std::ios::sync_with_stdio(false);

    int t = 1;
    int n, m;



    cin >> t;
    cin.ignore();


    vector<int> v;

    //Read input data
    for (int k = 0; k < t; ++k)
    {
        cin >> n >> m;
        Graph gr(&n);

        gr.visited.fill(0);
        gr.pred.fill(-99);
        gr.dist.fill(9999);



        gr.FillGraph(&n, &m);
        gr.DijkstrsSP(&m);

        v.push_back(gr.dist[n-1]);

    }


    cout << endl;

    for (int j = 0; j < t; ++j)
    {

        cout << "Case #" << j + 1 << ": ";

            cout << v[j] << " ";

        cout << endl;
    }
    return 0;
}
