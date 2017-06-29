#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>


using namespace std;

typedef struct info
{
    int itemID;
    int len;
    int score;


}info;

bool compareByValue(const info &a, const info &b)
{
    return ((double)a.score / a.len> (double)b.score/b.len);
}

typedef struct info_res
{
    int cs;
    vector <int> vi;
}info_res;

vector<info_res> vres;

int main()
{
    std::ios::sync_with_stdio(false);

    int t = 1;

    cin >> t;
    cin.ignore();

    //Read input data
    for (int k = 0; k < t; ++k)
    {
        int n, m;
        info inf1;
        info_res ir1;

        vector< info> vinf;

        // size of page, number of inf. pieces.
        cin >> m >> n;

        for (int i = 0; i < n; ++i)
        {
            cin>>  inf1.len >> inf1.score;
            inf1.itemID = i+1;
            vinf.push_back(inf1);
        }

        sort(vinf.begin(), vinf.end(), compareByValue);

        int filled = 0;
        int ix = 0;

        //set the case number for the output vector.
        ir1.cs = k;
        int curr_value = 0.0;

        while(filled <= m && ix < vinf.size())
        {
            curr_value = (vinf[ix].len);
            if ((filled + curr_value)<= m)
            {
                filled+=curr_value;

                //fill the output vector with topic numbers.
                ir1.vi.push_back(vinf[ix].itemID);

            }
            else
            {
                ix++;
            }
        }

        vres.push_back(ir1);


//        for (int j = 0; j < vinf.size(); ++j)
//        {
//            cout<<vinf[j].len << " ";
//        }

    }


    //output the results of all cases:
    for (int l = 0; l < vres.size(); ++l)
    {
        cout << "Case #" <<l+1<<": ";
        for (int j = 0; j < vres[l].vi.size(); ++j)
        {
            cout<< vres[l].vi[j] << " ";
        }
        cout << endl;
    }

    return 0;
}