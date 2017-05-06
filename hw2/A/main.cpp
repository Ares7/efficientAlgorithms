#include <unordered_map>
#include "vector"
#include "iostream"

using namespace std;

/*
 Partially based on the results of work at:
 www.techiedelight.com
 */

// class to represent a disjoint set
class DisjointSet {
    struct Row {
        int parid;
        int m;
    };
public:
    unordered_map<int, Row> parent;

//    parent[1].id=3;
//    parent[1].m=100;
//



    //only is needed to improve perf
    // stores the depth of trees
    unordered_map<int, int> rank;
public:
    // perform MakeSet operation
    void makeSet(vector<int> universe) {
        // create n disjoint sets (one for each item)
        for (int i : universe)
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

void printSets(vector<int> universe, DisjointSet &ds) {
    for (int i : universe)
        cout << ds.Find(i) << " ";

    cout << endl;
}

/*
 when marry it only means:
 1. 2 ppl we cant marry
 2. 2 fams become one. and have same root
    a. find root of a, b 
    b. union them.


 */

// main function
int main() {
    std::ios::sync_with_stdio(false);
//  cin.ignore();


    int t = 1;
    int n = 3;


    cin >> t;
    cin.ignore();

//    struct Cases {
//        int num;
//        int teams[1000][2];
//    };

    struct Cases {
        int a;//ppl, where #a is JF
        int b; // # relationships, b lines follow after a's ms
        int c; // # of marriages.

        int m[9999];
        vector<int> de;
        vector<int> fg;

    };

    vector<Cases> v;

    for (int k = 0; k < t; ++k)
    {

        Cases t;
        cin >> t.a >> t.b >> t.c;
        cin.ignore();

        for (int i = 0; i < t.a; ++i)
        {
            cin >> t.m[i];
            cin.ignore();
        }

        v.push_back(t);

    }

    for (int i = 0; i < t; ++i)
    {

        cout << v[i].a << v[i].b << v[i].c<<endl;
        for (int j = 0; j < v[i].a; ++j)
        {
            cout << v[i].m[j]<<endl;
        }

    }

    /*

    find most best option:
    for i < n

    if (parent[i].sum > parent[max|.sum)
        max=i

     */

    // universe of items
    vector<int> universe = {1, 2, 3, 4, 5};

    // initalize DisjointSet class
    DisjointSet ds;

    // create singleton set for each element of universe
    ds.makeSet(universe);
    printSets(universe, ds);

    ds.Union(4, 3); // 4 and 3 are in same set
    printSets(universe, ds);
    //NS 07 ID 06

    ds.Union(2, 1); // 1 and 2 are in same set
    printSets(universe, ds);

    ds.Union(1, 3); // 1, 2, 3, 4 are in same set
    ds.parent[1].m = 1000;

    printSets(universe, ds);

    return 0;
}