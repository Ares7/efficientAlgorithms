#include <iostream>
#include <vector>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);

    int k = 0;
    cin>>k;

    vector<string> results;
    string line;

    for (int i = 0; i < k; ++i)
    {
        cin>> line;
        results.push_back( line );
    }

    for (int i = 0; i < k; ++i) {
        cout << "Case #" <<i+1<<": Hello " << results[i] << "!"<<endl;
    }

    return 0;
}