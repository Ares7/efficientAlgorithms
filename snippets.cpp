#include <chrono>
using namespace std::chrono;
high_resolution_clock::time_point t1 = high_resolution_clock::now();
high_resolution_clock::time_point t2 = high_resolution_clock::now();
auto duration = duration_cast<microseconds>( t2 - t1 ).count();
cout << duration;



cout.precision(8);
int leftNum = stoi(items.substr(0, found));


std::list<unsigned> *adj_list;
adj_list = new list<unsigned>[v];
adj_list[src].push_back(dst);
for (it = adj_list[top].begin(); it != adj_list[top].end(); it++) 
{
	*it;
}


list<pair<int, int> > *neigb;
list<pair<int, int> >::iterator i;
neigb = new list<pair<int, int> >[*n];
neigb[a - 1].push_back(make_pair(b - 1, w));
for (i = neigb[u].begin(); i != neigb[u].end(); ++i)
    {
        // Get vertex label and weight of current adjacent
        // of u.
        int v = (*i).first;
        int weight = (*i).second;
    }




std::queue<unsigned> que;
que.push(entry_vertex);
while (que.size()) 
{
top = que.front();
que.pop();
}


priority_queue<pair<int, int>, vector<pair<int, int> > > pq;
pq.push(make_pair( 0, 0));
while(!pq.empty())
{
    int u = pq.top().second;
    pq.pop();
}


struct Row
{
int parid;
int m;


};

bool compareByID(const edges &a, const edges &b) {
return (a.a < b.a) || (a.a == b.a  && a.b < b.b);
}


unordered_map<int, Row> parent;
parent[i].parid = i;
parent[i].m = v[cnum].m[i];




typedef struct str_wins
{
int node;
int wins;
string answ;

bool operator()(const str_wins &x, const str_wins &y) const
{
return x.wins > y.wins;
}
}str_wins;
vector<vector<str_wins>> v;
for(auto& col:v)
{
	cout<<col.answ;

}



array<int, 250> visited;
visited.fill(0);



char **board = new char *[y];

for (int i = 0; i < y; i++)
{
    board[i] = new char[x];
    for (int j = 0; j < x; j++)
    {
        cin >> board[i][j];
    }
}
solveNQUtil(board);

