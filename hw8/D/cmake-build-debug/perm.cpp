#include <iostream>

int main()
{
    const int num_elems = 2;                      // number of set elements
    const int elems[num_elems] = {3, 5 };     // mapping of set element positions to values


    for (int s = 1; s < (1 << num_elems); ++s)    // iterate through all non-null sets
    {
        int sum = 0;
        // print the set
        std::cout << "{";
        for (int e = 0; e < num_elems; ++e)       // for each set element
        {
            if (s & (1 << e))                     // test for membership of set
            {
                std::cout << " " << elems[e];
                sum+=elems[e];
            }
        }
        std::cout << " }" << sum +1<< " "<<std::endl;

    }
    return 0;
}