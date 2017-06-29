#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
    std::ios::sync_with_stdio(false);
//
    int t = 1;
    vector<int> v;

    cin>>t;
    cin.ignore();

    for (int i = 1; i <= t; ++i)
    {
        int n,m;

        cin>>n>>m;

        int min = !(m<n)?n:m;
        for (int k = min; k >= 1; --k)
        {
            if(n%k==0 && m%k == 0)
            {
                v.push_back(k);
                break;
            }
        }
    }


    for (int l = 0; l < t; ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout<<v[l];
        cout << endl;
    }


    return 0;
}