#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>

using namespace std;

/*
 class to represent a disjoint set
 has an improved performance by using
 1. Path Compression
 2. Union by Rank
 */
class DisjointSet
{
    struct Row
    {
        int parid;
        int m;
    };

public:
    unordered_map<int, Row> parent;

    //only is needed to improve perf
    // stores the depth of trees
    unordered_map<int, int> rank;

public:
    // perform MakeSet operation
    void makeSet(int cnum)
    {
        // create a-1 disjoint sets (one for each item)
        for (int i = 0; i < v[cnum].a-1; ++i)
        {
            parent[i].parid = i;
            parent[i].m = v[cnum].m[i];
            rank[i] = 0;
        }

        //Fill JF data (additionally, bc he has no data on money)
        //HT has indices starting from 0, so -1 is neces.
        parent[v[cnum].a-1].parid = v[cnum].a-1;
        parent[v[cnum].a-1].m = 0;
        rank[v[cnum].a-1] = 0;

    }

    // Find the root of the set in which element k belongs
    int Find(int k) {
        // if k is not root
        if (parent[k].parid != k)
            // path compression
            parent[k].parid = Find(parent[k].parid);

        return parent[k].parid;
    }

    // Perform Union of two subsets
    void Union(int a, int b) {
        // find root of the sets in which elements
        // x and y belongs
        int x = Find(a);
        int y = Find(b);

        // if x and y are present in same set
        if (x == y)
            return;

        // Always attach smaller depth tree under the
        // root of the deeper tree.
        if (rank[x] > rank[y])
            parent[y].parid = x;
        else if (rank[x] < rank[y])
            parent[x].parid = y;
        else
        {
            parent[x].parid = y;
            rank[y]++;
        }
    }
};

//print roots
void printSets(int cnum, DisjointSet &ds)
{

    for (int i = 0; i < v[cnum].a; ++i)
    {
        int node = ds.Find(i);
        cout << "rich# "<<i+1 <<" has parent: "<< node +1<< " " << "and has money of "<<ds.parent[i].m;
        cout << endl;
    }
}


typedef struct Graph
{
       struct edges
       {
           int a;
           int b;
           int w;
       };
    vector<edges> ve;
};


int main()
{

    std::ios::sync_with_stdio(false);

    vector<string> v;
    int t = 1;

    cin >> t;
    cin.ignore();

    int n;

    DisjointSet ds;

    //Read input data
    for (int k = 0; k < t; ++k)
    {
        Graph gr;
        cin >> n ;

        for (int i = 0; i < n; ++i)
        {
            ds.makeSet(i);
            for (int j = i+1; j < n; ++j)
            {
                gr.ve[i].a = i;
                gr.ve[i].b = j;
                cin>>gr.ve[i].w;
            }


        }

        //ds.Union( ff, gg);
        cin.ignore();

    }


    for (int j = 0; j < t; ++j)
    {

        cout << "Case #" << j + 1 << ": " << v[j].data() << endl;

    }
    return 0;
}
