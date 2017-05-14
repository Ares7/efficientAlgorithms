
#include <iostream>
#include <vector>
#include <chrono>

//#define V 10000
#define P 10000

int V = 10000;
using namespace std;

using namespace std::chrono;
vector<string> v;
/*
partially adopted from www.sanfoundry.com

 */
bool PerformColorCheck (int v, bool **graph, int color[], int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

bool PerformColor(bool **graph, int m, int color[], int v)
{
    if (v == V)
        return true;
    for (int c = 1; c <= m; c++)
    {
        if (PerformColorCheck(v, graph, color, c))
        {
            color[v] = c;
            if (PerformColor (graph, m, color, v+1) == true)
                return true;
            color[v] = 0;
        }
    }
    return false;
}


bool graphColoring(bool **graph, int m)
{
    int *color = new int[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;
    if (PerformColor(graph, m, color, 0) == false)
        return false;
    return true;
}


void fillandCheck(int n, int m)
{
    int a = -1, b= -1;
    //static bool graph[V][V]= { 0 };



    cin >> n>> m;
    cin.ignore();


    bool **graph = new bool*[n];
    for (size_t i = 0; i < n; i++)
    {
        graph[i] = new bool[n];
    }

    V = n;

    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b ;

        if(a >=0 && b>= 0)
        {
            graph[a-1][b-1] = 1;
            graph[b-1][a-1] = 1;
        }


    }
    cin.ignore();

    //# of colors
    int c = 2;
    if (graphColoring (graph, c))
        v.push_back("yes");
    else
        v.push_back("no");
}

int main()
{


    std::ios::sync_with_stdio(false);

    int t = 1;

    cin >> t;
    cin.ignore();

    int n, m ;




    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //Read input data
    for (int k = 0; k < t; ++k)
    {


        fillandCheck(n, m);

//        cout << endl;
//        for (int j = 0; j < n; ++j)
//        {
//            for (int i = 0; i < n; ++i)
//            {
//                cout << graph[j][i] << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;
       //graph[V][V]= { false };

    }


    for (int j = 0; j < t; ++j)
    {

        cout<<"Case #" <<j+1 <<": " <<v[j].data()<<endl;

    }


    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    //cout << duration;

    return 0;
}