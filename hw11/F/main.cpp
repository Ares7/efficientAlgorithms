#include <unordered_map>
#include "vector"
#include "iostream"
#include "algorithm"

using namespace std;



struct fin
{
    int id;
    int sum;
};
vector<fin> vfin;

bool compareByID(const fin &a, const fin &b)
{
    return (a.sum < b.sum) || (a.sum == b.sum && a.id < b.id);
}

vector<int> v;

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
    };

public:
    unordered_map<int, Row> parent;

    //only is needed to improve perf
    // stores the depth of trees
    unordered_map<int, int> rank;
    unordered_map<int, int> nsubs;

public:
    // perform MakeSet operation
    void makeSet(int n)
    {
        // create a-1 disjoint sets (one for each item)
        for (int i = 0; i < n; ++i)
        {
            parent[i].parid = i;
            rank[i] = 0;
            nsubs[i]  =1;
        }

    }

    // Find the root of the set in which element k belongs
    int Find(int k)
    {
        // if k is not root
        if (parent[k].parid != k)
        {
            // path compression
            parent[k].parid = Find(parent[k].parid);
        }

        return parent[k].parid;
    }

    // Perform Union of two subsets
    void Union(int a, int b)
    {
        // find root of the sets in which elements
        // x and y belongs
        int x = Find(a);
        int y = Find(b);

        // if x and y are present in same set
        if (x == y)
        {
            return;
        }

        // Always attach smaller depth tree under the
        // root of the deeper tree.
        if (rank[x] > rank[y])
        {
            parent[y].parid = x;
            nsubs[x] = nsubs[x] + nsubs[y];
        }
        else if (rank[x] < rank[y])
        {
            parent[x].parid = y;
            nsubs[y] = nsubs[y] + nsubs[x];
        }
        else
        {
            parent[x].parid = y;
            rank[y]++;
            nsubs[y] = nsubs[y] + nsubs[x];
        }
    }


};

//print roots
void printSets(int n, DisjointSet &ds)
{

    for (int i = 0; i < n; ++i)
    {
        int parent = ds.Find(i);
        cout << "satellite# " << i + 1 << " has parent: " << parent + 1 <<
             " and has # of subnodes: " << ds.nsubs[i];
        cout << endl;
    }
}


int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie();

    DisjointSet ds;
    int t = 1, n, m, a, b;

    cin >> t;
    cin.ignore();


    //Read input data
    for (int k = 0; k < t; ++k)
    {
        cin >> n >> m;
        cin.ignore();
        vfin.clear();


        ds.makeSet(n);


        for (int i = 0; i < m; ++i)
        {
            cin >> a >> b;
            ds.Union(a - 1, b - 1);
        }

        //printSets(n, ds);
        //cout << ds.rank[4];

        fin fn;
        int  maxsubs = 0, x;

        for (int l = 0; l < n; ++l)
        {
            //maxrk = 0;

            if(ds.nsubs[l] > maxsubs )
            {
                maxsubs =ds.nsubs[l];
            }
        }

        for (int l = 0; l < n; ++l)
        {
            x = ds.Find(l);
            if(ds.nsubs[x] == maxsubs)
            {
                fn.id = l;
                fn.sum = n-maxsubs;
                vfin.push_back(fn);
            }

        }
        sort(vfin.begin(), vfin.end(), compareByID);
        v.push_back(vfin[0].id);


    }


    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": " << v[l]+1 << endl;

    }


    return 0;
}