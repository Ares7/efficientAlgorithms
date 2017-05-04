#include <iostream>
#include <vector>
#include "cmath"

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
//
    int t = 1;
    string s ;
    vector<long long int> v;

    cin>>t;
    cin.ignore();

    for (int i = 1; i <= t; ++i)
    {
        getline(cin, s);

        int pos =0 ;
        long long int res = 0;

/*
 *

3
1plus12minus3
5tothepowerof5minus3
1minus8times5tothepowerof3

 */
        int numStartPos = 0;
        string oper="nope";

        while (pos<s.length())
        {
            long long int num = 0;

            int numLen = 0;


            int strStartPos;
            int strLen = 0;


            while(isdigit(s[pos])==true)
            {
                numLen++;
                pos++;
            }
            num=atoi(s.substr(numStartPos, numLen).c_str());

            if (oper=="nope")
            {
                res = num;
            }

            if (oper=="plus")
            {
                res = res+ num;
            }
            if (oper=="minus")
            {
                res = res - num;
            }
            if (oper=="times")
            {
                res = res*num;
            }
            if (oper=="tothepowerof")
            {
                res = pow(res, num);
            }

            strStartPos = pos;
            while(isdigit(s[pos])==false)
            {
                strLen++;
                pos++;
            }
            oper=s.substr(strStartPos, strLen).c_str();

            numStartPos = pos;
        }
        v.push_back(res);
    }


    for (int l = 0; l < t; ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout<<v[l];
        cout << endl;
    }


    return 0;
}