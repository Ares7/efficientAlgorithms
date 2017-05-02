#include <iostream>
#include <vector>

using namespace std;



int main() {
    std::ios::sync_with_stdio(false);
//
    int t = 1;
    string s ;

    getline(cin, s);
    //cin.ignore();
    vector<int> v;
    int pos =0 ;

    int res = 0;
    while (pos<s.length())
    {
        int num = 0;
        int startPos = pos;
        int numPos = 0;
        while(isdigit(s[pos])==true)
        {
            numPos++;
            pos++;
        }
        num=atoi(s.substr(startPos, numPos).c_str());
        pos++;
        res = num;
    }
    //cout<<s[1];
    v.push_back(res);


    for (int l = 0; l < t; ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout<<v[l];
        cout << endl;
    }

    return 0;
}
