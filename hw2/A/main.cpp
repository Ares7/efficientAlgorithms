#include <unordered_map>
#include "vector"
#include "iostream"

using namespace std;

/*
 Partially based on the results of work at:
 www.techiedelight.com
 */

struct de
{
    int d;
    int e;
};
struct fg
{
    int f;
    int g;
};

struct Cases {
    int a;//ppl, where #a is JF
    int b; // # relationships, b lines follow after a's ms
    int c; // # of marriages.

    int m[10000];  // money money money


    vector<de> vde; // relationships pairs
    vector<fg> vfg;// marriage pairs

};

vector<Cases> v;
vector<int> vbest;



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

//    parent[1].id=3;
//    parent[1].m=100;
//



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

/*
 when marry it only means:
 1. 2 ppl we cant marry
 2. 2 fams become one. and have same root
    a. find root of a, b 
    b. union them.
 3. set m to -m for both nodes.


 */

// main function
int main() {
    std::ios::sync_with_stdio(false);

    int t = 1;

    cin >> t;
    cin.ignore();


    //Read input data
    for (int k = 0; k < t; ++k)
    {

        Cases t;
        cin >> t.a >> t.b >> t.c;
        cin.ignore();

        //Read Money data
        for (int i = 0; i < t.a-1; ++i)
        {
            cin >> t.m[i];
            cin.ignore();
        }

        //Read Relationships data
        for (int j = 0; j < t.b; ++j)
        {
            de de1;
            cin>>de1.d >> de1.e;
            cin.ignore();
            t.vde.push_back(de1);
        }

        //Read Marriages data
        for (int j = 0; j < t.c; ++j)
        {
            fg fg1;
            cin>>fg1.f >> fg1.g;
            cin.ignore();
            t.vfg.push_back(fg1);
        }
        
        v.push_back(t);

    }

    DisjointSet ds;

    //FILL the UNION-FIND
    for (int i = 0; i < t; ++i)
    {
        // initalize DisjointSet class
        ds.makeSet(i);
        //ds.Union(1,2);

        //unite those ppl that have relationships
        for (int j = 0; j < v[i].b; ++j)
        {

            //fix indexes bc input is given starting 1
            int dd =v[i].vde[j].d -1 ;
            int ee =v[i].vde[j].e -1;
            ds.Union( dd, ee);
        }


        //printSets(i, ds);

        //manage Marriages
        for (int j = 0; j < v[i].c; ++j)
        {
            //fix indexes bc input is given starting 1
            int ff =v[i].vfg[j].f -1 ;
            int gg =v[i].vfg[j].g -1;
            ds.Union( ff, gg);

            //make the ppl that got married unattractive.
            ds.parent[ff].m  = -99;
            ds.parent[gg].m  = -99;
        }
        printSets(i, ds);


        /*

   find  best option:
   for i < n

   if (parent[i].sum > parent[max|.sum)
       max=i

    consider only from diff fams
    */

        //Find best Marriage Candidate
        int indx = 0;
        int sum = -99;
        //int x = ds.Find(max);
        int JF = ds.Find(v[i].a-1);

        for (int j = 0; j < v[i].a -1 ; ++j)
        {
            int y = ds.Find(j);
            //check if potential partner is from diff family
            if (y!=JF)
            {
                if (ds.parent[j].m > sum)
                {
                    sum = ds.parent[j].m;
                    indx=j;
                }
            }

        }

        //cout << "Best potential Candiadate ID is: "<< max+1<< endl;
        vbest.push_back(ds.parent[indx].m);
        //cin.ignore();


    }


    for (int l = 0; l < t; ++l)
    {
        if (vbest[l] >= 0)
        cout<< "Case #"<<l+1 <<": "<<vbest[l] << endl;
        else
            cout<< "Case #"<<l+1 <<": "<<"impossible"<< endl;
    }


    return 0;
}