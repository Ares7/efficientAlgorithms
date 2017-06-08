/*
 partially adopted form
 stanfordacm
 */

#include <cmath>
#include <vector>
#include <iostream>
#include "climits"
#include <algorithm>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;


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

vector<str_wins> wins;

bool compareByID( str_wins &x,  str_wins &y)
{
	return x.node < y.node;
}


struct MaxFlow {

	int N;
	int M;
	int numbN;

	int posA;
	int posB;

	VVI cap, flow;
	VI dad, Q;

	MaxFlow(int N, int M, int NN) :
	N(N), cap(N, VI(N)), flow(N, VI(N)), dad(N), Q(N)
	{
		this->numbN = NN;
		this->posA = 0;
		this->posB = N - 1;
		this->M = M;
	}

	void AddEdge(int from, int to, int cap)
	{
		this->cap[from][to] += cap;
	}

	int BlockingFlow(int s, int t)
	{
		fill(dad.begin(), dad.end(), -1);
		dad[s] = -2;

		int head = 0, tail = 0;
		Q[tail++] = s;
		while (head < tail)
		{
			int x = Q[head++];
			for (int i = 0; i < N; i++)
			{
				if (dad[i] == -1 && cap[x][i] - flow[x][i] > 0)
				{
					dad[i] = x;
					Q[tail++] = i;
				}
			}
		}

		if (dad[t] == -1) return 0;

		int totflow = 0;
		for (int i = 0; i < N; i++)
		{
			if (dad[i] == -1) continue;

			int amt = cap[i][t] - flow[i][t];
			for (int j = i; amt && j != s; j = dad[j])
				amt = min(amt, cap[dad[j] ][j] - flow[dad[j] ][j]);
			if (amt == 0) continue;
			flow[i][t] += amt;
			flow[t][i] -= amt;
			for (int j = i; j != s; j = dad[j])
			{
				flow[dad[j] ][j] += amt;
				flow[j][dad[j]] -= amt;
			}
			totflow += amt;
		}

		return totflow;
	}

	int GetMaxFlow(int source, int sink)
	{
		int totflow = 0;
		while (int flow = BlockingFlow(source, sink))
			totflow += flow;

		return totflow;
	}

	int FillGraph()
	{

		str_wins sw;
		int a, b;

		//process the previous wins
		for (int i = 1; i <= this->numbN ; ++i)
		{
			sw.node = i;
			cin >> sw.wins;

			wins.push_back(sw);

			//connect S with all the teams.
			this->AddEdge(this->posA, i, INT_MAX);

		}

		for(int i = 1; i<=this->M; i++)
		{



			cin>>a >>b;

			//connect Teams bw each other to represent Matches to be played.
			this->AddEdge(a , this->numbN+b, 1);
			this->AddEdge(b , this->numbN+ a, 1);

			//connect Teams with T.
			this->AddEdge(this->numbN+a , this->posB, 1);
			this->AddEdge(this->numbN+b , this->posB, 1);

		}

		return 0;
	}



};

int main() {

	vector<vector<str_wins>> v;
	std::ios::sync_with_stdio(false);

	int t = 1;

	cin >> t;
	cin.ignore();

	//Read input data
	for (int k = 0; k < t; ++k)
	{
		int n, m;

		cin >> n >> m;

		MaxFlow mf( 2*n + 2, m, n);
		mf.FillGraph();

		mf.GetMaxFlow(mf.posA, mf.posB);

		sort(wins.begin(), wins.end(), str_wins() );
		int max_wins = wins[0].wins;


		for (int i = 0; i<n; i++)
		{
			if(mf.flow[i+n+1][mf.N-1] + wins[i].wins >= max_wins)
			{
				wins[i].answ = "yes ";
			}
			else
			{
				wins[i].answ = "no ";
			}

		}

		sort(wins.begin(), wins.end(), compareByID );

		v.push_back(wins);

	}

	int j = 1;
	for (auto& row:v)
	{
		//int max_wins = row[0].wins;

		cout << "Case #" << j << ": ";

			for(auto& col:row)
			{
				cout<<col.answ;

			}

		//cout << v[j];
		j++;
		
		cout << endl;
	}
}

