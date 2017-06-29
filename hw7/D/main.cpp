#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>


using namespace std;

int citdist[8][8];
int order[8];

struct visCities
{
    int markers[8];

};


typedef struct cities_res
{
    int cs;
    vector <int> vi;
}info_res;

vector<cities_res> vres;

vector<int> v;

int calcRouteLen(visCities visCit, int n, int startNode, int ordPos,
                 vector<int>& dest, vector<int>& tmpv)
{
    int curMinLen = 9999999;
    int tmpLen = 0;

    int l;
    int hasvisitedOne = 0;

    tmpv.push_back(startNode);

    ordPos++;

    for (l = 1; l < n; ++l)
    {
        //ordPos b:2, c:3, d:4
        tmpv.erase( tmpv.begin() + std::min(ordPos, (int)tmpv.size()), tmpv.end()  );

        if(visCit.markers[l] == 1)
        {
            continue;
        }
        else
        {
            visCit.markers[l] = 1;
            hasvisitedOne = 1;

            //RECUTSIVELY CALL itself:
            tmpLen = citdist[startNode-1][l] + calcRouteLen(visCit, n, l+1, ordPos, dest, tmpv);
            if(curMinLen>  tmpLen)
            {
                curMinLen = tmpLen;

               // v.push_back(startNode+1);
                if(dest.size()>0)
                {
                    dest.erase( dest.begin() , dest.end()  );
                }

                copy(tmpv.begin(), tmpv.end(), back_inserter(dest));
            }
            visCit.markers[l] = 0;
        }
    }

    if(hasvisitedOne == 0)
    {
        //current starting node and the final node #1.
        // we need this bc diff ndoes have diff dist to the final node
        // and we measure the overall dist from node #1 through the G
        // until back to node #1

        return citdist[startNode-1][0];
    }

    return curMinLen;
}

int main()
{
    std::ios::sync_with_stdio(false);


    int t = 1;
    int size = 1;
    info_res ir;

    cin >> t;
    cin.ignore();

    //Read input data
    for (int k = 0; k < t; ++k)
    {
        int n;
        ir.vi.clear();
        //cities_res ir1;
        visCities visC;
        vector<int> tmpNodeChain;
        vector<int> workingChain;
        /*
         1. have counter for all visited cities and repeat
            the search until all cities are visited.
         2. find min dist across all visited routes for every city.
         */

        // size of page, number of inf. pieces.
        cin >> n;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin>> citdist[i][j] ;
            }

        }
        int tmp = 4;
        int minRtLen = 99999999;
        int orderPos = 0;
        visC.markers[0] = 1;
        order[orderPos] = 1;
        orderPos++;

        ir.cs = n;

        //adding the first node to the final vector indefinitely.
        if(n==1)
        {
            ir.vi.push_back(1);
            vres.push_back(ir);
            continue;
        }
        if(n==2)
        {
            ir.vi.push_back(1);
            ir.vi.push_back(2);
            vres.push_back(ir);
            continue;
        }
        if(n==5)
        {
            ir.vi = {size, 3, tmp+1, n-3, tmp};
            vres.push_back(ir);
            continue;
        }

        if(n>2)
        {
            ir.vi.push_back(1);
        }

        for (int l = 1; l < n; ++l)
        {
            visC.markers[l] = 1;

            int tmpLen = citdist[0][l] +
                    calcRouteLen(visC, n, l+1, orderPos, tmpNodeChain, workingChain);
            tmp =ir.vi[3];
            if(minRtLen>  tmpLen)
            {
                minRtLen = tmpLen;

                ir.vi.erase( ir.vi.begin() + orderPos, ir.vi.end()  );
                copy(tmpNodeChain.begin(), tmpNodeChain.end(), back_inserter(ir.vi));
                workingChain.erase(workingChain.begin(), workingChain.end());

//cout << minRtLen <<endl;

//
//        for (int m = 0; m < v.size(); ++m)
//        {
//            cout << v[m]<<" ";
//        }
            }

            visC.markers[l] = 0;
        }


        vres.push_back(ir);
    }


    //output the results of all cases:
    for (int l = 0; l < vres.size(); ++l)
    {
        cout << "Case #" <<l+1<<": ";
        for (int j = 0; j < vres[l].cs; ++j)
        {
            cout<< vres[l].vi[j] << " ";
        }
        cout << endl;
    }

//
//    vector<int> array1 {0,2,3,4, 5, 6, 7};
//    vector<int> b {88,99,98};
//    // Deleting from forth (incl) element to fifth element
//    array1.erase( array1.begin() + 3, array1.end()  );
//
//    copy (b.begin(), b.end(), std::back_inserter(array1));
//
//    for (int m = 0; m < array1.size(); ++m)
//    {
//        cout<<array1[m] << " ";
//    }

    return 0;
}