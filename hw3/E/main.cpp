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

    //int m;
    int a;
    int b;
    int w;

    //for the sorting by the weight of the sound
    bool operator()(const edges &x, const edges &y) const {
        return (x.a < y.a) || (x.a == y.a && x.w < y.w);
    }
};


typedef struct InputSet {

    vector<edges> ve;
} Graph;

struct setofCases {
    int size;
    vector<edges> vend;
};

void FillInputSet(InputSet *gr, int PartitArr[], int n, int *maxDist) {

    //int arr[n];
    PartitArr[0] = -99;
    int partition = 0;
    int indx = 1;

    *maxDist = 0;
    // read every line of the sound block
    for (int i = 0; i < n; ++i)
    {

        vector<int> vdist;
        int dist;

        //grab the entire row on input sound levels
        for (int l = 0; l < n; ++l)
        {
            cin >> dist;
            vdist.push_back(dist);

            if (i == 0 && l == n - 1)
            {
                *maxDist = dist;
            }
        }

        if (n != 1)
        {
            for (int j = i + 1; j < n; ++j)
            {
                partition++;

                edges edg;
                edg.a = i + 1;
                edg.b = j + 1;
                edg.w = vdist[j];
                //edg.m = 0;

                gr->ve.push_back(edg);


            }

            indx++;
            PartitArr[indx] = partition;

        }
        else
        {
            edges edg;
            edg.a = 1;
            edg.b = 1;
            edg.w = 0;
            //edg.m = 0;

            gr->ve.push_back(edg);
        }

        //for index of partitions



    }

//    for (int k = 0; k < n; ++k)
//    {
//        cout << PartitArr[k] << endl;
//    }

    //sort based on the weight of an edge. (works as PQ.)
    sort(gr->ve.begin(), gr->ve.end(), edges());
}


void FillHT(InputSet *gr) {

    //dists.push (2);
    struct nodes {
        int b;
        queue<int> dists;
    };

//    unordered_map<int, nodes>  edges;
//
//    for (int i = 0; i < gr->ve.size(); ++i)
//    {
//        edges.insert(gr->ve[i].b, )
//    }

}

int main() {

    std::ios::sync_with_stdio(false);

    int t = 1;

    cin >> t;
    cin.ignore();

    string inpt;


    DisjointSet ds;
    vector<edges> res;


    vector<int> v;

    //Read input data
    for (int k = 0; k < t; ++k)
    {
        InputSet gr;
        int maxDist;

        res.clear();


        int n;
        cin >> n;
        int partitArr[n];
        FillInputSet(&gr, partitArr, n, &maxDist);

        //vector starts from zero, but PArtitArr contains beginning indexes from 1.
        int startPartit = partitArr[1];

        //check if EXISTS for small n!
        int endPartit = partitArr[2];


        int sum = 0;
        int marks[151] = {0};

        //putting node 1 into the list of final elements.
        v.push_back(gr.ve[startPartit].a);

        /*
         finding the set of elements that will allow us to move to node n (uncle).
         while making sure that the distance is not bigger than
         the guaranteed distance from the node 1 to the uncle.
        */
         while (startPartit < endPartit)
        {
            //chk B node for some edge isnt market(visited): globally
            if ( marks[gr.ve[startPartit].b] == 1)
            {
                startPartit++;
                continue;
            }


            if ( sum + gr.ve[startPartit].w <= maxDist)
            {
                //found the first node with lowest value of dist,
                //mark this node.
                //gr.ve[startPartit].m = 1;
                marks[gr.ve[startPartit].b] = 1;

                sum += gr.ve[startPartit].w;

                v.push_back(gr.ve[startPartit].b);

                if(gr.ve[startPartit].b == n)
                {
                    break;
                }

                startPartit = partitArr[gr.ve[startPartit].b];

                //start pos has just changed, so same assignment:
                endPartit  = partitArr[gr.ve[startPartit].b];
                continue;
            }
            else
            {
                /*
                 1. unmark current node from global table
                 2. ?find another node in the same partition

                 3. handle the case when there are no more elements in
                    the partition to check, so reverting to previous element.

                */
                int tmp = v.size();

                int lastEl = v[tmp-1];
                v.erase( v.begin() +  tmp-1); // Deleting the third element

                marks[lastEl] = 0;

                // go back to prev el.
                startPartit = partitArr[lastEl];
                endPartit  = partitArr[lastEl+1];
                continue;

            }

            startPartit++;

        }



        //FillHT(&gr);

    }


    cout << endl;

    for (int j = 0; j < t; ++j)
    {

        cout << "Case #" << j + 1 << ": " ;

        for (int i = 0; i < v.size(); ++i)
        {
            cout << v[i] << " ";
            //cout<< res[i].a +1<< " " << v[i].  res[i].b+1<< endl;
        }

        cout<< endl;
    }
    return 0;
}
