// REF: geeksforgeeks.org/bipartite-graph/
#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph {
private:
    enum color_t {G_NONE, G_RED, G_BLUE};
    unsigned vertices;
    std::list<unsigned> *adj_list;
    bool is_partitie_core(color_t [], unsigned);
public:
    Graph(unsigned);
    ~Graph();
    void add_edge(unsigned, unsigned);
    bool is_partitie2();
};

Graph::Graph(unsigned v)
{
    vertices = v;
    adj_list = new std::list<unsigned>[v];
}

Graph::~Graph()
{
    delete [] adj_list;
}

void Graph::add_edge(unsigned src, unsigned dst)
{
    /* it must be a undirected graph */
    adj_list[src].push_back(dst);
    adj_list[dst].push_back(src);
}

bool Graph::is_partitie_core(color_t colors[], unsigned entry_vertex)
{
    /* assign the first color */
    colors[entry_vertex] = G_RED;

    /* create a queue(FIFO) to store colored vertices */
    std::queue<unsigned> que;
    que.push(entry_vertex);

    unsigned top;
    /* determine an alternate color according to current top of queue */
    color_t alt;
    std::list<unsigned>::iterator it;
    while (que.size()) {
        top = que.front();
        que.pop();
        alt = (colors[top] == G_RED) ? G_BLUE : G_RED;

        /* iterate for all adjacent vertices of `top' */
        for (it = adj_list[top].begin(); it != adj_list[top].end(); it++) {
            /* if current adjacent vertex non-colored */
            if (colors[*it] == G_NONE) {
                colors[*it] = alt;
                que.push(*it);
            }
                /* if current adjacent color the same color with its parent
                 *  we claim that it's not a bipartitie graph
                 * */
            else if (colors[*it] == colors[top])
                return false;
        }
    }

    return true;
}

bool Graph::is_partitie2()
{
    color_t colors[vertices];
    for (unsigned i = 0; i < vertices; i++)
        colors[i] = G_NONE;

    /* handle the case of disconnected graph
     *  time complexity: O(V*(V+E)) = O(V*V+V*E)
     * */
    for (unsigned i = 0; i < vertices; i++)
        /* only recur for unvisited vertices */
        if (colors[i] == G_NONE)
            if (is_partitie_core(colors, i) == false)
                return false;

    return true;
}

int main()
{

    std::ios::sync_with_stdio(false);

    vector<string> v;
    int t = 1;

    cin >> t;
    cin.ignore();

    int n, m;


    //Read input data
    for (int k = 0; k < t; ++k)
    {

        cin >> n >> m;
        int a, b;

        Graph g1(n);

        for (int i = 0; i < m; ++i)
        {
            cin >> a >> b;
            g1.add_edge(a - 1, b - 1);
        }

        if (g1.is_partitie2())
        {
            v.push_back("yes");
        } else
        {
            v.push_back("no");
        }
        cin.ignore();

    }


    for (int j = 0; j < t; ++j)
    {

        cout << "Case #" << j + 1 << ": " << v[j].data() << endl;

    }
    return 0;
}
