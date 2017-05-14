#include <unordered_map>
#include "vector"
#include "iostream"
#include <set>

using namespace std;

/*
 Partially based on the results of work at:
 www.techiedelight.com
 */

struct xy {
    string r;
    int x;
    int y;
};

struct Cases {
    int n; //ppl, where #1 is Lea
    int m; // # relationships

    vector<xy> vxy; // relationships pairs

};

vector<Cases> v;

vector<string> vans;


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
        parent[cnum].parid = cnum;
        rank[cnum] = 0;

    }

    // Find the root of the set in which element k belongs
    int Find(int k) {
        // if k is root
        if (parent[k].parid == k)
            return k;

        // recurse for parent until we find root
        return Find(parent[k].parid);

    }

    // Perform Union of two subsets
    void Union(int a, int b) {
        // find root of the sets in which elements
        // x and y belongs
        int x = Find(a);
        int y = Find(b);

        parent[x].parid = y;
    }
};

//print roots
void printSets(DisjointSet &ds, set<int> countries) {

    for (int i: countries)
    {
        int node = ds.Find(i);
        cout << "country #" << i << " has relationships with: " << node << " ";
        cout << endl;
    }
}


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
        cin >> t.n >> t.m;
        cin.ignore();

        //Read Relationships data
        for (int j = 0; j < t.m; ++j)
        {
            xy xy1;
            cin >> xy1.r >> xy1.x >> xy1.y;
            cin.ignore();
            t.vxy.push_back(xy1);
        }

        v.push_back(t);

    }

    DisjointSet dsf;
    DisjointSet dsa;

    //FILL the UNION-FIND
    for (int i = 0; i < t; ++i)
    {
        //vector<int> friends;
        set<int> friends;
        //vector<int> antis;

        set<int> antis;
        //unite those ppl that have relationships
        for (int j = 0; j < v[i].m; ++j)
        {
            //FRIENDSHIPS
            if (v[i].vxy[j].r == "F")
            {
                friends.insert(v[i].vxy[j].x);
                friends.insert(v[i].vxy[j].y);
//                friends.push_back();
//                friends.push_back(v[i].vxy[j].y);

                dsf.makeSet(v[i].vxy[j].x);
                dsf.makeSet(v[i].vxy[j].y);
                dsf.Union(v[i].vxy[j].x, v[i].vxy[j].y);
            }
            //ANTIPATHIES
            else
            {
                antis.insert(v[i].vxy[j].x);
                antis.insert(v[i].vxy[j].y);

                dsa.makeSet(v[i].vxy[j].x);
                dsa.makeSet(v[i].vxy[j].y);
                dsa.Union(v[i].vxy[j].x, v[i].vxy[j].y);
            }
        }

        //not nec for the alg to work:
        printSets(dsf, friends);
        cout<<endl;
        printSets(dsa, antis);

        //making Rule #4 work
        // (if one hates same as the other, they form alliance):
        for (int xx : antis)
        {
            int x = dsa.Find(xx);

            for (int yy : antis)
            {
                int y = dsa.Find(yy);

                if(x==y && xx!=yy)
                {
                    if(friends.find(x) != friends.end())
                    {
                        friends.insert(x);
                        dsf.makeSet(x);
                    }
                    if(friends.find(y) != friends.end())
                    {
                        friends.insert(y);
                        dsf.makeSet(y);
                    }
                    dsf.Union(x, y);
                }


            }

        }

        //making Rule #5 work
        // (if one hates same as the other, they form alliance):
        for (int xx : friends)
        {
            int x = dsf.Find(xx);

            for (int yy : friends)
            {
                int y = dsf.Find(yy);

                if(x==y && xx!=yy)
                {
                    if(antis.find(x) != antis.end())
                    {
                        antis.insert(x);
                        dsa.makeSet(x);
                    }
                    if(antis.find(y) != antis.end())
                    {
                        antis.insert(y);
                        dsa.makeSet(y);
                    }
                    dsa.Union(x, y);
                }


            }

        }

        printSets(dsf, friends);
        cout<<endl;

        /*
         Handle Rule #4:

         if we have A a b in input
         1. then we add A and B into the 2nd UF
         2. by going through every node seen so far for every node that has
            the same root as A in 1st DS, we unite this node
            with B in the 2nd DS.
         3. for every node that has the same root as B in 1st DS, we unite this node
         with A in the 2nd DS.


         Handle Rule #5:
         if we have F a b in input
         1. then we add A and B into the 2nd UF
         2. for every node that has the same root as A in 1st DS, we unite this node
         with B in the 2nd DS.
         3. for every node that has the same root as B in 1st DS, we unite this node
         with A in the 2nd DS.


         */

    }



    for (int l = 0; l < t; ++l)
    {
        //cout<< "Case #"<<l+1 <<": "<<v[l].n << endl;
    }


    return 0;
}