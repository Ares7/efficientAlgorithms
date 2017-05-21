#include <iostream>
#include <list>
#include <queue>
#include <array>

using namespace std;

typedef struct selectedStations
{
	int length;
	vector<int> st;
}selectedStations;


class Graph {

	int N;
	list<pair<int, int> > *neigb;
	list<pair<int, int> >::iterator i;


public:

	array<int, 250> visited;
	array<int, 250> pred;
	array<int, 250> dist;

	vector<int> stations;

public:



	Graph(int *n) {
		this->N = *n;
		neigb = new list<pair<int, int> >[*n];
	}

	void FillGraph(int *n, int *m, int *s) {

		int si;
		// read every line of the sound block
		for (int i = 0; i < *m; ++i)
			{
			int a, b, w;

			cin >> a >> b >> w;
			neigb[a - 1].push_back(make_pair(b - 1, w));
			neigb[b - 1].push_back(make_pair(a - 1, w));
			}

		for (int j = 0; j < *s; ++j)
			{
			cin >> si;
			stations.push_back(si);
			}

	}

	bool operator()(pair<int, int> n1, pair<int, int> n2) {
		return n1.second > n2.second;
	}

	void DijkstrsSP(int *m) {


		/*
		 template<
		 class T,
		 class Container = std::vector<T>,
		 class Compare = std::less<typename Container::value_type>
		 > class priority_queue;

		 Weight is used used as first item  of pair
		 as first item is by default used to compare
		 two pairs. the 2nd item is the node to which the dist applies.
		 */


		priority_queue<pair<int, int>, vector<pair<int, int> > > pq;

		visited[0] = 1;
		dist[0] = 0;
		pred[0] = -99;

		pq.push(make_pair(0, 0));

		while (!pq.empty())
			{
			int u = pq.top().second;
			pq.pop();

			for (i = neigb[u].begin(); i != neigb[u].end(); ++i)
				{
				// Get vertex label and weight of current adjacent
				// of u.
				int v = (*i).first;
				int weight = (*i).second;

				if (dist[v] > (dist[u] + weight))
					{
					visited[v] = 0;
					}
				if (visited[v] == 0)
					{
					if (dist[v] > dist[u] + weight)
						{
						dist[v] = dist[u] + weight;

						// re-check all nodes that have incoming edge
						// from the updated node to update their distances.

						pq.push(make_pair(dist[v] + weight, v));
						pred[v] = u;
						visited[v] = 0;
						} else
							{
							visited[v] = 1;
							}

					}


				}
			}


	}
};


int main() {

	std::ios::sync_with_stdio(false);

	int t = 1;
	int n, m, s;


	cin >> t;
	cin.ignore();


	//vector<int> v;


	vector <selectedStations> vfin;
	//Read input data
	for (int k = 0; k < t; ++k)
		{
		cin >> n >> m >> s;
		Graph gr(&n);

		gr.visited.fill(0);
		gr.pred.fill(-99);
		gr.dist.fill(9999);

		selectedStations selStat;
		//vfin.clear();
		//gr.stations.fill(-1);


		gr.FillGraph(&n, &m, &s);
		gr.DijkstrsSP(&m);


		int mdx = gr.stations[0] - 1;
		for (int i = 0; i < s; ++i)
			{

			if (gr.dist[gr.stations[i] - 1] < gr.dist[mdx])
				{
				mdx = gr.stations[i] - 1;
				}
			}


		selStat.length = gr.dist[mdx];

		for (int j = 0; j < s; ++j)
			{
			if(gr.dist[gr.stations[j] -1] == gr.dist[mdx])
				{
				selStat.st.push_back(gr.stations[j]);

				}
			}
		vfin.push_back(selStat);

		}


	cout << endl;

	for (int j = 0; j < t; ++j)
		{

		cout << "Case #" << j + 1 << ": ";

		cout << vfin[j].length << " ";

		for (int i = 0; i < vfin[j].st.size(); ++i)
			{
			cout<< vfin[j].st[i] << " ";
			}

		cout << endl;
		}
	return 0;
}

