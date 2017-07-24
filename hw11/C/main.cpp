#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;


struct cases
{
    int n, x, y;
};



int main() {
    std::ios::sync_with_stdio(false);
//
    int t = 1;
    cases cs;

    vector<cases> v;
    ostringstream oss;

    cin>>t;
    cin.ignore();

    for (int i = 1; i <= t; ++i)
    {
        int n;
        cin>>cs.n >> cs.y ;

        
        //oss << 12341234123412341234;

        v.push_back(cs);
    }






    for (int l = 0; l < t; ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout<<v[l].x;
        cout << endl;
    }


    return 0;
}