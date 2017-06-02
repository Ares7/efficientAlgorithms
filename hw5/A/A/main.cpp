#include <iostream>
#include <list>
#include <queue>
#include "unordered_map"

using namespace std;

/*
 parts of the solution were adopted from
 http://www.geeksforgeeks.org/
 */
vector<int> v;

class Graph
{

	int N;
	//first: node, second its weight
public:
	list<pair<int, int> > *neigb;
	list<pair<int, int> >::iterator i;



public:



	int posA;
	int posB;


	int FillGraph()
	{

		int n, m;
		//cout << "enter:";
		cin >> n >> m;

		this->N = n;
		this->posA = 0;
		this->posB = n - 1;
		neigb = new list<pair<int, int> >[n];

		for (int i = 0; i < m; ++i)
		{

			int x, y, z;
			cin >> x >> y >> z;
			//if not self-looped
			if (x != y)
			{
				//if we add additional edge with smaller or bigger weight value.
				neigb[x - 1].push_back(make_pair(y - 1, z));
				neigb[y - 1].push_back(make_pair(x - 1, z));

			}

		}

		return 0;
	}

	/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */

	bool bfs( int s, int t, int parent[])
	{
		// Create a visited array and mark all vertices as not visited
		bool visited[this->N];
		memset(visited, 0, sizeof(visited));

		// Create a queue, enqueue source vertex and mark source vertex
		// as visited
		queue <int> q;
		q.push(s);
		visited[s] = true;
		parent[s] = -1;

		// Standard BFS Loop
		while (!q.empty())
		{
			int u = q.front();
			q.pop();


			for (i = neigb[u].begin(); i != neigb[u].end(); ++i)
			{
				// Get vertex label and weight of current adjacent
				// of u.
				int v = (*i).first;
				int weight = (*i).second;

				if (visited[v]==false && weight > 0)
				{
					q.push(v);
					parent[v] = u;
					visited[v] = true;
				}

			}
		}

		// If we reached sink in BFS starting from source, then return
		// true, else false
		return (visited[t] == true);
	}
};




int main()
{

	std::ios::sync_with_stdio(false);

	int t = 1;

	cin >> t;
	cin.ignore();

	//Read input data
	for (int k = 0; k < t; ++k)
	{

		Graph gr;
		//gr.edges.clear();



		//graph was filled successfully
		if (gr.FillGraph() == 0)
		{
			int parent[500] = {0};
			cout<< gr.bfs(gr.posA, gr.posB, parent);

		}


	}


	cout << endl;

	for (int j = 0; j < t; ++j)
	{

		cout << "Case #" << j + 1 << ": ";

//		if (v[j] == -1 )
//		{
//			cout << "impossible";
//		}
//		else
//		{
//			cout << v[j] << ":" << v[j];
//		}
		cout << endl;
	}
	return 0;
}
