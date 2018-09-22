#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// method to add an edge to the adjacency list
void addEdge(vector<int> adj[], int x, int y)
{
	adj[x].push_back(y);
}

int main()
{
    // user input:
	// n = number of stages of the potion (nodes)
	// m = number of relations for making the stages (edges)
	// (a,b) = relation between the 2 stages of the potion
	//		in order to make the b'th stage of the potion, a'th stage must be completed
	// indegree = array that stores the indegree of each node
	// adj = adjacency list representation of the graph
	int n;
	int m;
	int a;
	int b;
	cin >> n >> m;
	int indegree[n] = {0};
	vector<int> adj[n];

	// priority heap for lexical ordering
	priority_queue <int, vector<int>, greater<int>> queue;
	
	// computing indegrees of each node and adding them to the adjacency list
	for(int i = 1; i <= m; i++)
	{
		cin >> a >> b;
		indegree[b - 1]++;
		addEdge(adj, a - 1, b - 1);
	}
	
	// for(int i = 0; i < (sizeof(indegree)/sizeof(*indegree)); i++)
	// {
		// cout << indegree[i] << "\n";
	// }
	
	// put all the nodes with indegree 0 into the priority queue
	for(int i = 0; i < n; i++)
	{
		if(indegree[i] == 0)
		{
			queue.push(i);
		}
	}
	
	// remove min from priority queue and perform the following:
	// 		1. increment count of visited nodes
	// 		2. decrease in-degree by 1 for all its neighboring nodes
	// 		3. if in-degree of a neighboring nodes is 0, then add it to the priority queue
	// repeat until the priority queues is empty
	int counter = 0;
	int output[n];
	while(!queue.empty())
	{
		int node = queue.top();
		queue.pop();
		output[counter] = node;
		counter++;
		for(int i = 0; i < adj[node].size(); i++)	
		{
			indegree[adj[node][i]]--;
			if(indegree[adj[node][i]] == 0)
			{
				queue.push(adj[node][i]);
			}
		}
	}
	
	// if counter is not equal to the number of nodes, then there is no top-sort, and return -1
	if(counter != n)
	{
		cout << -1;
	}
	else
	{
		for(int i = 0; i < n; i++)
		{
			cout << output[i] + 1 << " ";
		}
	}
	
    return 0;
}
