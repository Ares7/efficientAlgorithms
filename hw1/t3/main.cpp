#include <iostream>
#include <vector>
#include "regex"

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
//
    int t = 1;
    int n = 3;

    cin>>t;
    cin>>n;
    cin.ignore();

    vector<string> results;
    string line;

    for (int i = 0; i < n; ++i)
    {
        getline(cin, line);
        results.push_back(line);
    }

// ich bin ein student
// a potent element went through a vent
// ein zentner enten enthaelt keine studenten
    for (int j = 0; j < n; ++j)
    {
        results[j] = regex_replace(results[j], regex("enten"), "ierende");
        results[j] = regex_replace(results[j], regex("entin"), "ierende");
        results[j] = regex_replace(results[j], regex("ent"), "ierender");
    }


    cout << "Case #" << t << ":" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << results[i] << endl;
    }

    return 0;
}