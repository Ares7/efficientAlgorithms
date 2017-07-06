#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std::chrono;


using namespace std;

typedef struct vsol
{
    int col;
    vector<int> els;
} vsol;

vector<vsol> v;
vector<int> vnums;
vector<int> vfilter;
vector<int> vpr;


int calcTwoPrimes(vsol &vs, int l)
{
    for (int j = 0; j < vpr.size(); ++j)
    {
        if (binary_search(vpr.begin(), vpr.end(), vnums[l]-vpr[j]))
        {
            vs.els.push_back(vpr[j]);
            vs.els.push_back(vnums[l]-vpr[j]);
            return 0;
        }

    }

    return -1;
}


int calcThreePrimes(vsol &vs, int l)
{
    for (int i = 0; i < vpr.size(); ++i)
    {
        for (int j = 0; j < vpr.size(); ++j)
        {
            //k
            if (binary_search(vpr.begin(), vpr.end(), vnums[l]-vpr[i]-vpr[j]))
            {
                vs.els.push_back(vpr[i]);
                vs.els.push_back(vpr[j]);
                vs.els.push_back(vnums[l]-vpr[i]-vpr[j]);
                return 0;
            }

        }
    }
    return -1;
}


int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);
//
    int t = 1;



    cin >> t;
    cin.ignore();
    int max = 2;
    vfilter.push_back(max);

    for (int i = 1; i <= t; ++i)
    {
        int n;
        cin >> n;
        if (n > max)
        {
            //filling the numbers to later filter out everything that is not prime.
            for (int j = max+1; j <= n; ++j)
            {
                vfilter.push_back(j);
            }
            max = n;
        }
        //putting input case numbers into the vector.
        vnums.push_back(n);
    }


    int i;
    //filtering all nubmers that are not prime
    // remember that the numbers start from 2 and indices from 0!
    for (int k = 0; k < vfilter.size(); ++k)
    {
        if (vfilter[k] != -1)
        {
            i = vfilter[k];
            vpr.push_back(i);
            //i = sqrt(i);
            int ixRem = k;

            while (ixRem < vfilter.size())
            {
                vfilter[ixRem] = -1;
                ixRem += i;
            }
        }

    }


    for (int l = 0; l < vnums.size(); ++l)
    {
        vsol vs;
        //chk for even:
        if (!(vnums[l]& 1))
        {
            vs.col = 2;
            calcTwoPrimes(vs, l);


        }
        else
        {
            vs.col = 3;
            //there should be approx k = log2(n) primes in total.
            //so, overall ~ k^3 = 18.768 operations.
            calcThreePrimes(vs, l);

        }

        v.push_back(vs);

    }

//    for (int k = 0; k < vs.els.size(); ++k)
//    {
//        cout <<vs.els[k] << " ";
//    }



    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        for (int i = 0; i < v[l].col; ++i)
        {
            cout << v[l].els[i] << " ";
        }

        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    return 0;
}