#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <map>

using namespace std::chrono;


using namespace std;
//partially adapted from lplessard.blogspot.de


vector<uint64_t> v;
vector<uint64_t> vfr;

std::map<std::pair<long long, long long>, long long> memo;

long long combinations(long long n, long long k, long long p){
   if (n  < k) return 0;
   if (0 == n) return 0;
   if (0 == k) return 1;
   if (n == k) return 1;
   if (1 == k) return n;

   map<std::pair<long long, long long>, long long>::iterator it;

   if((it = memo.find(std::make_pair(n, k))) != memo.end()) {
        return it->second;
   }
   else
   {
        long long value = (combinations(n-1, k-1,p)%p + combinations(n-1, k,p)%p)%p;
        memo.insert(std::make_pair(std::make_pair(n, k), value));
        return value;
   }
}

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::ios::sync_with_stdio(false);
//
    int t = 1;

    //cin >> t;
    cin.ignore();


    for (int i = 1; i <= t; ++i)
    {
        uint64_t n, fr;
        int size = 0;
        //cin >> n;

        //lcm(a,b,c) = lcm(lcm(a,b),c)
        for (int j = 0; j < n; ++j)
        {
            //putting input friends wishes into the vector.
            //cin >> fr;
        }

        v.push_back(combinations(5,2, 223092870));


    }


    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout << v[l];
        cout << endl;
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    cout << duration;
    return 0;
}