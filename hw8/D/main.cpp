#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std::chrono;


using namespace std;
//partially adapted from lplessard.blogspot.de


vector<uint64_t> v;
vector<uint64_t> vfr;

uint64_t gcd(uint64_t a, uint64_t b)
{
    uint64_t c;
    while (a != 0)
    {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

uint64_t lcm(uint64_t a, uint64_t b)
{
    return (b / gcd(a, b)) * a;
}

uint64_t lcm_arr(uint64_t *n, uint64_t size)
{
    uint64_t last_lcm, i;

    if (size < 2)
    { return 0; }

    last_lcm = lcm(n[0], n[1]);

    for (i = 2; i < size; i++)
    {
        last_lcm = lcm(last_lcm, n[i]);
    }

    return last_lcm;
}

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);
//
    int t = 1;

    cin >> t;
    cin.ignore();


    for (uint64_t i = 1; i <= t; ++i)
    {
        uint64_t n, fr;
        int size = 0;
        cin >> n;
        uint64_t *arr, *fr_came;
        arr = new uint64_t[15];

        //~2*15^2 * 100
        fr_came = new uint64_t[40000];
        vfr.clear();

        //lcm(a,b,c) = lcm(lcm(a,b),c)
        for (int j = 0; j < n; ++j)
        {
            //putting input friends wishes into the vector.
            cin >> fr;
            arr[j] = fr;
        }

        if (n == 1)
        {
            v.push_back(fr + 1);
            continue;
        }

        //generating all counts of friends that might come:
        for (int s = 1; s < (1 << n); ++s)
        {
            uint64_t sum = 0;
            for (int q = 0; q < n; ++q)
            {
                // test for membership of the set
                if (s & (1 << q))
                {
                    sum += arr[q];
                }
            }

            size++;
            fr_came[s - 1] = sum + 1;

        }


//        for (uint64_t k = 0; k < vfr.size(); ++k)
//        {
//            cout << vfr[k] << " "<<std::endl;
//        }

        //passing the list of possible friends combinations to calculate lcm:
        v.push_back(lcm_arr(fr_came, size));

        delete[] arr;
        delete[] fr_came;

    }


    for (uint64_t l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout << v[l];
        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    //cout << duration;
    //cout << sizeof(uint64_t);
    return 0;
}