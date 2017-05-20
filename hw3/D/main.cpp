#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>


/*
 * Partially based on the results at:
 * www.techiedelight.com
 */

using namespace std;

/*
 class to represent a disjoint set
 has an improved performance by using
 1. Path Compression
 2. Union by Rank
 */
class DisjointSet {
    struct Row {
        int parid;
    };

public:
    unordered_map<int, Row> parent;

    //only is needed to improve perf
    // stores the depth of trees
    unordered_map<int, int> rank;

public:
    // perform MakeSet operation
    void makeSet(int cnum) {
        // create a-1 disjoint sets (one for each item)
        for (int i = 0; i < cnum; ++i)
        {
            parent[i].parid = i;
            rank[i] = 0;
        }

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
void printSets(int cnum, DisjointSet &ds) {

    //for (int i = 0; i < v[cnum].a; ++i)
//    {
//        int node = ds.Find(i);
//        cout << "rich# "<<i+1 <<" has parent: "<< node +1<< " " << "and has money of "<<ds.parent[i].m;
//        cout << endl;
//    }
}

struct edges {
    int a;
    int b;
    int w;

    //for the sorting by the capcity of the road.
    bool operator()(const edges &x, const edges &y) const {
        return x.w > y.w;
    }
};

typedef struct InputSet {

    vector<edges> ve;
} Graph;

struct setofCases
{
    int size;
    vector<edges> vend;
};

////for the sorting i < j for every pair (i,j)


// sort to satisfy (2):
bool compareByID(const edges &a, const edges &b) {
    return (a.a < b.a) || (a.a == b.a  && a.b < b.b);
}


int main() {

    std::ios::sync_with_stdio(false);

    int t = 1;

    cin >> t;
    cin.ignore();

    string inpt;
    int n;

    DisjointSet ds;
    vector<edges> res;


    vector< setofCases> v;




    //Read input data
    for (int k = 0; k < t; ++k)
    {
        InputSet gr;

        res.clear();


        cin >> n;


        // read every line of the sound block
        for (int i = 0; i < n ; ++i)
        {

            vector<int> snd;
            int sound;

            //grab the entire row on input sound levels
            for (int l = 0; l < n; ++l)
            {
                cin >> sound;
                snd.push_back(sound);
            }

            if(n !=1)
            {
                for (int j = i + 1; j < n; ++j)
                {
                    edges edg;
                    edg.a = i;
                    edg.b = j;
                    edg.w = snd[j];

                    gr.ve.push_back(edg);

                }
            }
            else
            {
                edges edg;
                edg.a = 0;
                edg.b = 0;
                edg.w = 0;

                gr.ve.push_back(edg);
            }

        }


        //gr.ve.erase(gr.ve.end());


        //sort based on the weight of an edge. (works as PQ.)
        std::sort(gr.ve.begin(), gr.ve.end(), edges());

        ds.makeSet(n);
        edges efin;

        //go through every edge and check if its endpoints
        // are in the UF
        // -1 comes from the alg: we need to check E-1 to form MST of size V
        int offset = 0;
        if (gr.ve.size() == 1)
        {
            offset = 0;
        } else
        {
            offset = 1;
        }
        for (int m = 0; m < gr.ve.size() - offset; ++m)
        {
            int x = ds.Find(gr.ve[m].a);
            int y = ds.Find(gr.ve[m].b);

            // if two nodes of some edge are not in the same
            // subset, then adding the edge will not create
            // a cycle.

            if (x != y)
            {
                ds.Union(gr.ve[m].a, gr.ve[m].b);

                //for a structure with edges and nodes that got into the MST
                efin.a = gr.ve[m].a;
                efin.b = gr.ve[m].b;
                efin.w = gr.ve[m].w;

                res.push_back(efin);

            }

            else
            {
                continue;
            }
        }

        cin.ignore();

        //sorting by the ID of the connecting nodes
        std::sort(res.begin(), res.end(), compareByID);

        //put the final vector into the final set of cases.

        setofCases soc;
        soc.size = res.size();
        soc.vend = res;
        v.push_back(soc);

    }


    cout << endl;

    for (int j = 0; j < t; ++j)
    {
        if (res.size() > 0)
        {
            cout << "Case #" << j + 1 << ":" << endl;
        }
        for (int i = 0; i < v[j].size; ++i)
        {
            cout << v[j].vend[i].a + 1 << " " << v[j].vend[i].b+ 1 << endl;
            //cout<< res[i].a +1<< " " << v[i].  res[i].b+1<< endl;
        }

    }
    return 0;
}
