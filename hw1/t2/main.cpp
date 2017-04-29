#include <iostream>
#include <vector>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);

    int const c = 299792458;
    int k = 0;

    cin>>k;

    vector<long long> results;
    long int line;

    for (int i = 0; i < k; ++i)
    {
        cin>> line;
        results.push_back( line*c*c );
    }

    for (int i = 0; i < k; ++i) {
        cout << "Case #" <<i+1<<": " << results[i] <<endl;
    }

    return 0;
}