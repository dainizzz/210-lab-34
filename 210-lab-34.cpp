// COMSC-210 | Lab 34 | Dainiz Almazan
// IDE used: CLion

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 11;

struct Edge {
	int src, dest, weight;
};

typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
	vector<vector<Pair> > adjList;

	Graph(vector<Edge> const &edges) {
		adjList.resize(SIZE);
		for (auto &edge: edges) {
			int src = edge.src;
			int dest = edge.dest;
			int weight = edge.weight;

			adjList[src].push_back(make_pair(dest, weight));
			adjList[dest].push_back(make_pair(src, weight)); // undirected
		}
	}

	// Print adjacency list
	void printGraph() {
		cout << "Graph's adjacency list:" << endl;
		for (int i = 0; i < adjList.size(); i++) {
			cout << i << " --> ";
			for (Pair v: adjList[i])
				cout << "(" << v.first << ", " << v.second << ") ";
			cout << endl;
		}
	}

	// ---- DEPTH FIRST SEARCH ----
	void DFS(int start) {
		vector<bool> visited(SIZE, false);
		stack<int> st;

		st.push(start);

		cout << "DFS starting from vertex" << start << ":" << endl;

		while (!st.empty()) {
			int v = st.top();
			st.pop();

			if (!visited[v]) {
				cout << v << " ";
				visited[v] = true;

				// Push neighbors in the original order
				for (auto &p: adjList[v]) {
					int neighbor = p.first;
					if (!visited[neighbor]) {
						st.push(neighbor);
					}
				}
			}
		}

		cout << endl;
	}


	// ---- BREADTH FIRST SEARCH ----
	void BFS(int start) {
		vector<bool> visited(SIZE, false);
		queue<int> q;

		visited[start] = true;
		q.push(start);

		cout << "BFS starting from vertex " << start << ":" << endl;

		while (!q.empty()) {
			int v = q.front();
			q.pop();
			cout << v << " ";

			// Visit neighbors
			for (auto &p: adjList[v]) {
				int neighbor = p.first;
				if (!visited[neighbor]) {
					visited[neighbor] = true;
					q.push(neighbor);
				}
			}
		}
		cout << endl;
	}
};


int main() {
	vector<Edge> edges = {
		{0, 1, 2}, {0, 2, 7}, {0, 3, 1},
		{1, 5, 3}, {2, 3, 10},{2, 4, 8}, {2, 6, 5},
		{4, 7, 4}, {6, 7, 3}, {6, 8, 15},
		{7, 9, 6}, {9, 10, 9}
	};

	Graph graph(edges);

	graph.printGraph();

	cout << endl;
	graph.DFS(0); // start DFS at node 0
	graph.BFS(0); // start BFS at node 0

	return 0;
}
