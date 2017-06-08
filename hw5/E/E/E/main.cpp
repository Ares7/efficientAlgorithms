/*
 partially adopted form
 stanfordacm
 */

#include <cmath>
#include <vector>
#include <iostream>
#include "climits"

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;


struct MaxFlow {

	int N;
	int M;
	int P;
	int S;

	int posA;
	int posB;



	VVI cap, flow;
	VI dad, Q;

	MaxFlow(int N, int M, int P, int S) :
	N(N), cap(N, VI(N)), flow(N, VI(N)), dad(N), Q(N)
	{
		this->P = P;
		this->S = S;
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

		if(totflow>this->P)
		{
			return totflow=this->P;
		}

		return totflow;
	}

	int FillGraph()
	{
		int nw = this->N  - this->M - this->S-2;
		//process the warriors
		for (int i = this->N - nw-1; i < this->N -1 ; ++i)
		{

			int c, k, ki;
			cin >> c >> k;

			//connect the warrior with t.
			this->AddEdge(i, this->N-1, c);

			//connect the warrior with the Spells.
			for(int j = 1; j <=k; j++)
			{
				cin>>ki;
				this->AddEdge(this->M + 1 + ki-1, i, INT_MAX);

			}


		}

		//process the sorcers
		for (int i = 1; i <= this->M; ++i)
		{

			int a, ti;
			cin >> a ;
			cin.ignore();
			this->AddEdge(this->posA, i, INT_MAX);

			//connect magitians with spells
			for(int j = 1; j <=a; j++)
			{
				cin>>ti;
				this->AddEdge(i, ti + this->M, INT_MAX);

			}

		}

		return 0;
	}

};

int main() {

	vector<int> v;
	std::ios::sync_with_stdio(false);

	int t = 1;

	cin >> t;
	cin.ignore();

	//Read input data
	for (int k = 0; k < t; ++k)
	{
		int n, m, p, s;
		//cout << "enter:";
		cin >> n >> m >> p >> s;

		MaxFlow mf( n + m + s + 2, m, p ,s);
		mf.FillGraph();

		v.push_back(mf.GetMaxFlow(mf.posA, mf.posB));

	}

	for (int j = 0; j < t; ++j)
	{

		cout << "Case #" << j + 1 << ": ";

		cout << v[j];


		cout << endl;
	}
}

