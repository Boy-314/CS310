#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// method to add an edge to the adjacency list
void addEdge(vector<int> adj[], int x, int y)
{
	adj[x].push_back(y);
}

// coloring key:
// 		white (0) = unvisited
// 		gray (1) = currently exploring
// 		black (2) = finished exploring
// if node's neighbor is gray, node->neighbor is a back edge
int DFS(int node, int color[], int parent[], vector<int> adj[])
{
	if(color[node] == 0)
	{
		color[node] = 1;
		for(int i = 0; i < adj[node].size(); i++)
		{
			if(color[adj[node][i]] == 0)
			{
				parent[adj[node][i]] = node;
				return DFS(adj[node][i],color,parent,adj);
			}
			else if(color[adj[node][i]] == 1)
			{
				parent[adj[node][i]] = node;
				return adj[node][i];
			}
		}
		color[node] = 2;
	}
	return -1;
}

bool calculateAndOutputCycle(int n, int color[], int parent[], vector<int> adj[], int start)
{
	int result = DFS(start,color,parent,adj);
	// cout << "result: " << result << endl;
	// for(int i = 0; i < n; i++)
	// {
		// cout << parent[i] << " ";
	// }
	if(result != -1)
	{
		cout << 1 << "\n";
		int temp = parent[result];
		int backwards[n] = {-1};
		int counter = 0;
		while(temp != result)
		{
			// cout << "one" << endl;
			backwards[counter] = temp + 1;
			// cout << "two" << endl;
			counter++;
			// cout << "three" << endl;
			cout << "temp: " << temp << endl;
			temp = parent[temp];
			// cout << "four" << endl;
		}
		cout << result + 1 << " ";
		counter--;
		while(counter >= 0)
		{
			cout << backwards[counter] << " ";
			counter--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
    // user input:
	// n = number of rooms (number of nodes)
	// m = passages that connect two rooms (number of edges)
	// (a,b) = passage from a to b (edges)
	// color = coloring array for the nodes
	int n;
	int m;
	int a;
	int b;
	cin >> n >> m;
	int color[n];
	int parent[n];
	vector<int> adj[n];
	
	// convert user input into adjacency list
	for(int i = 0; i < m; i++)
	{
		cin >> a >> b;
		addEdge(adj, a - 1, b - 1);
	}
	
	// make all the nodes initialize with white coloring
	for(int i = 0; i < n; i++)
	{
		color[i] = 0;
	}
	
	// set all parents of nodes to -1
	for(int i = 0; i < n; i++)
	{
		parent[i] = -1;
	}

	// run DFS with coloring nodes
	for(int i = 0; i < n; i++)
	{
		if(parent[i] == -1 && calculateAndOutputCycle(n, color, parent, adj, i))
		{
			return 0;
		}
	}
	
	cout << 0;
	
    return 0;
}
