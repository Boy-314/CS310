#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

class CompareDistance
{
	public:
		bool operator()(pair<int,int> x, pair<int,int> y)
		{
			return x.second > y.second;
		}
};

// method to add an edge to the adjacency list
void addEdge(vector<pair<int,int>> adj[], int x, int y, int z)
{
	pair<int, int> p;
	p.first = y;
	p.second = z;
	adj[x].push_back(p);
}

// method for implementing dijkstra's algorithm
int dijkstra(int size, vector<pair<int,int>> adj[], int start)
{
	int distance[size];
	for(int i = 0; i < size; i++)
	{
		distance[i] = 10000000;
	}
	priority_queue<pair<int,int>, vector<pair<int,int>>, CompareDistance> heap;
	distance[start] = 0;
	pair<int,int> base;
	base.first = start;
	base.second = 0;
	heap.push(base);
	int v = 0;
	while(!heap.empty())
	{
		heap.pop();
		for(int i = 0; i < adj[v].size(); i++)
		{
			if(distance[adj[v][i].first] > distance[v] + adj[v][i].second)
			{
				cout << "updating distance array" << endl;
				distance[adj[v][i].first] = distance[v] + adj[v][i].second;
			}
			pair<int,int> temp;
			temp.first = distance[adj[v][i].first];
			temp.second = adj[v][i].second;
			heap.push(temp);
			cout << "heap.top().first : " << heap.top().first << endl;
			for(int i = 0; i < size; i++)
			{
				cout << "distance[" << i << "] : " << distance[i] << endl;
			}
			cout << endl;
		}
		v++;
		if(v >= size)
			return distance[size-1];
	}
	return distance[size - 1];
}

int main()
{
	// user input:
	// n = number of crossroads (nodes)
	// m = number of roads connecting them (edges)
	// (a,b,c) = a road from a to b with c indicating it has the reservoir if c is 1 and a parched road if c is 2
	// adj = adjacency list containing the edges and colors of said edges (c coordinate)
	int n;
	int m;
	int a;
	int b;
	int c;
	cin >> n >> m;
	vector<pair<int,int>> adj[2*n];
	for(int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		addEdge(adj, a-1, b-1, c-1);
		addEdge(adj, a+n-1, b+n-1, c-1);
		if(c == 1)
		{
			addEdge(adj, a-1, b+n-1, c-1);
		}
	}
	if(dijkstra(2*n, adj, 0) + 1 > 2*n)
	{
		cout << -1;
	}
	else
	{
		cout << dijkstra(2*n, adj, 0);
	}
    return 0;
}
