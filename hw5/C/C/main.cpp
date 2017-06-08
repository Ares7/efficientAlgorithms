/*
 partially adopted form
 stanfordacm and
 https://stackoverflow.com/questions/236129/split-a-string-in-c
 */

#include <cmath>
#include <vector>
#include <iostream>
#include "unordered_map"

#include <sstream>

#include <iterator>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;


struct MaxFlow {

	int N;
	int M;
	int posA;
	int posB;



	VVI cap, flow;
	VI dad, Q;

	MaxFlow( int N, int M) :
	N(N+M+2), cap(N+M+2, VI(N+M+2)), flow(N+M+2, VI(N+M+2)), dad(N+M+2), Q(N+M+2)
	{

		this->posA = 0;
		//+2 to compensate s,t and -1 to compensate index from 0.
		this->posB = N +M+2- 1;
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


	template<typename Out>
	void split(const std::string &s, char delim, Out result) {
		stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			*(result++) = item;
		}
	}

	vector<string> split(const string &s, char delim) {
		vector<string> elems;
		split(s, delim, back_inserter(elems));
		return elems;
	}


	int FillGraph()
	{
		int Nsize = this->N -this->M-2;
		//connect s with all printers.
		for(int i = 1; i<= Nsize; i++)
		{
			this->AddEdge(0, i, 1);
		}
		cin.ignore();

		unordered_map<int, int> exp;

		//connect every printer with possible pages it can print.
		string line;

		int lnum=0;

		vector<string> inpt ;
		vector<string> nodes ;

		while (getline(cin, line))
		{
			lnum++;

			if(line.length()>0)
			{

				inpt = split(line, ',');

				for(int i = 0; i < inpt.size(); i++)
				{
					string items = inpt[i].data();

					size_t found = items.find("-");
					if (found!=string::npos)
					{
						string tmp =items.substr(0, found);
						int leftNum = stoi(items.substr(0, found));
						tmp =items.substr(found+1, items.length());
						int rightNum = stoi(items.substr(found+1, items.length()));

						for (int z = leftNum; z <=rightNum; z++)
						{
							this->AddEdge(lnum, z+ Nsize, 1);
							exp.insert(make_pair(z+ Nsize,z+ Nsize));
						}
					}
					else
					{
						int n = stoi(items) +Nsize;

						this->AddEdge(lnum, n, 1);

						exp.insert(make_pair(n,n));

						continue;
					}

				}
			}
			else
			{
				break;
			}


		}

		//connect all pages with t.
		for(int i = Nsize+1; i<= Nsize + this->M; i++)
		{
			this->AddEdge(i, this->N-1, 1);
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
		int n, m;
		//cout << "enter:";
		cin >> n >> m;

		MaxFlow mf( n, m);
		mf.FillGraph();

		if(mf.GetMaxFlow(mf.posA, mf.posB) == mf.M)
		{
			v.push_back(1);
		}
		else
		{
			v.push_back(-1);
		}



	}

	for (int j = 0; j < t; ++j)
	{

		cout << "Case #" << j + 1 << ": ";
		
		if (v[j] <1 )
		{
			cout << "no";
		}
		else
		{
			cout << "yes" ;
		}
		cout << endl;
	}
}

