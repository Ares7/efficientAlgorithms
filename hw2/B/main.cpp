#include <iostream>
#include <iomanip>
#include <vector>
//#include <chrono>
using namespace std;
//using namespace std::chrono;
int main() {
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();
    std::ios::sync_with_stdio(false);

    int t = 1;

    cout.precision(8);
    //cout << "Pi: " << fixed << res << endl;

    cin >> t;
    cin.ignore();

    int d, p, u, v;
    vector<double> dists;


    //Read input data
    for (int k = 0; k < t; ++k)
    {
        cin>>d >> p>> u>>v;
        //cin.ignore();

        double s = (d- (v-u))/(double)p;

        if(s==0)
        {
            s = d/4;
        }

        double step = s/2;

        while( step>=0.0001)
        {
            double prval = 0;
            vector<double> points;
            points.push_back(prval);

            //Perform points assignment:
            for (int i = 1; i <= p; ++i)
            {

                if(prval+s <= u)
                {
                    points.push_back(prval+s);
                    prval += s;
                }
                else if (prval+s > u && prval+s < v)
                {
                    prval = v-s;
                }
                else if(prval+s >= v)
                {
                    points.push_back(prval+s);
                    prval += s;
                }

            }
            if(points[p-1]>d)
            {
                s -= step;
                step = step/2;
                s += step;
            }
            else
            {
                s += step;
            }

        }
        dists.push_back(s);

    }

    for (int j = 0; j < t; ++j)
    {
        cout<<"Case #" <<j+1 <<": "<< fixed <<dists[j]<<" "<<endl;
    }
    //std::cout << "Hello, World!" << std::endl;

    //high_resolution_clock::time_point t2 = high_resolution_clock::now();

    //auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    //cout << duration;

    return 0;
}