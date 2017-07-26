#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <chrono>
using namespace std::chrono;
using namespace std;

struct cases
{
    int n, x, y;
};

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);
//
    int t = 1, slendiff, ix;

    string sc, sfin;
    cases cs;

    vector<cases> v;

    cin>>t;
    cin.ignore();

    for (int i = 1; i <= t; ++i)
    {
        cin>>cs.n >> cs.y ;

        sc = string(cs.n-1, '0');
        sc.insert(sc.length(), "1");

        ix = 1;
        while(1)
        {
            sfin = to_string(cs.y * ix);
            if(sfin.length() > cs.n )
            {
                //take the ending of length cs.n only
                sfin = sfin.substr(sfin.size() - cs.n);
            }

            slendiff =  cs.n- sfin.length();
            //ck if pad is needed.
            if (slendiff > 0)
            {
                for (int j = 0; j < slendiff; ++j)
                {
                    sfin.insert(j, "0");
                }

            }

            if(sfin.compare(sc) == 0)
            {
                break;
            }
            else
            {
                ix = ix+2;
            }
        }
        cs.x = ix;

        v.push_back(cs);
    }


    for (int l = 0; l < t; ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout<<v[l].x;
        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
    //cout << duration;

    return 0;
}