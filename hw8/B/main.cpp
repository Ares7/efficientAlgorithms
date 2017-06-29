#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct vsol
{
    int col;
    vector <int> els;
}vsol;

vector <vsol> v;
vector <int> vnums;
vector <int> vfilter;
vector <int> vpr;


int calcTwoPrimes(vsol &vs, int l)
{

        for (int j = 0; j < vpr.size(); ++j)
        {
            for (int k = 0; k < vpr.size(); ++k)
            {

                if( vpr[j] + vpr[k] == vnums[l])
                {
                    vs.els.push_back(vpr[j]);
                    vs.els.push_back(vpr[k]);

                    return 0;
                }


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
            for (int k = 0; k < vpr.size(); ++k)
            {

                if(vpr[i] + vpr[j] + vpr[k] == vnums[l])
                {
                    vs.els.push_back(vpr[i]);
                    vs.els.push_back(vpr[j]);
                    vs.els.push_back(vpr[k]);

                    return 0;
                }


            }
        }
    }
    return -1;
}


int main()
{
    std::ios::sync_with_stdio(false);
//
    int t = 1;
    vsol vs;

    cin>>t;
    cin.ignore();
    int max = 0;

    for (int i = 1; i <= t; ++i)
    {
        int n;
        cin>>n;
        if(n>max)
        {
            max = n;
        }
        //putting input case numbers into the vector.
        vnums.push_back(n);
    }

    //filling the numbers to later filter out everything that is not prime.
    for (int j = 2; j <= max; ++j)
    {
        vfilter.push_back(j);
    }

    int i;
    //filtering all nubmers that are not prime
    // remember that the numbers start from 2 and indices from 0!
    for (int k = 0; k < vfilter.size(); ++k)
    {
        if(vfilter[k]!=-1)
        {
            i = vfilter[k];
            vpr.push_back(i);
        }

        while(i< vfilter.size())
        {
            vfilter[i] = -1;
            i+=i;
        }

    }



    for (int l = 0; l < vnums.size(); ++l)
    {
        //chk for even:
        if(vnums[l]%2 == 0)
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



    }

    for (int k = 0; k < vs.els.size(); ++k)
    {
        cout <<vs.els[k] << " ";
    }




//    for (int l = 0; l < t; ++l)
//    {
//        cout << "Case #" << l + 1 << ": ";
//        //for (int i = 0; i < v[l].els; ++i)
//        {
//            //cout<<v[l].els[];
//        }
//
//        cout << endl;
//    }


    return 0;
}