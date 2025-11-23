// COMSC-210 | Lab 34 | Dainiz Almazan
// IDE used: CLion

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 11;

// A lookup table so airport 0 = "ATL", 1 = "LAX", etc.
vector<string> AIRPORTS = {
	"ATL", "LAX", "ORD", "DFW", "DEN",
	"JFK", "SEA", "MIA", "PHX", "CLT", "BOS"
};

struct Edge {
	int src, dest, weight; // weight = ticket cost
};

typedef pair<int, int> Pair;

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
			adjList[dest].push_back(make_pair(src, weight)); // undirected flights
		}
	}

	// Print adjacency list
	void printGraph() {
		cout << "\nAvailable Flights (Airport --> (Destination, Ticket Cost)):\n";
		for (int i = 0; i < adjList.size(); i++) {
			cout << AIRPORTS[i] << " --> ";
			for (Pair v: adjList[i]) {
				cout << "(" << AIRPORTS[v.first] << ", $" << v.second << ") ";
			}
			cout << endl;
		}
		cout << endl;
	}

	// BFS for minimum layovers
	void minimumLayovers(int start, int dest) {
		vector<bool> visited(SIZE, false);
		vector<int> dist(SIZE, -1);
		queue<int> q;

		visited[start] = true;
		dist[start] = 0;
		q.push(start);

		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (auto &p: adjList[v]) {
				int neighbor = p.first;
				if (!visited[neighbor]) {
					visited[neighbor] = true;
					dist[neighbor] = dist[v] + 1;
					q.push(neighbor);
				}
			}
		}

		cout << "\nMinimum layovers from " << AIRPORTS[start] << " to " << AIRPORTS[dest] << ": ";
		if (dist[dest] == -1) cout << "No route available.";
		else cout << dist[dest] << " layovers.";
		cout << "\n\n";
	}

	// BFS: List all reachable AIRPORTS
	void reachableAirports(int start) {
		vector<bool> visited(SIZE, false);
		queue<int> q;
		visited[start] = true;
		q.push(start);


		cout << "Reachable AIRPORTS from " << AIRPORTS[start] << ":\n";
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			cout << AIRPORTS[v] << " ";

			for (auto &p: adjList[v]) {
				if (!visited[p.first]) {
					visited[p.first] = true;
					q.push(p.first);
				}
			}
		}
		cout << "\n\n";
	}

	// Dijkstra for cheapest route (shortest path)
	void cheapestRoutesFrom(int start) {
		const int INF = 1e9;
		vector<int> cost(SIZE, INF), parent(SIZE, -1);
		priority_queue<Pair, vector<Pair>, greater<Pair> > pq;

		cost[start] = 0;
		pq.push({0, start});

		while (!pq.empty()) {
			auto [c, u] = pq.top();
			pq.pop();
			if (c > cost[u]) continue;

			for (auto &p: adjList[u]) {
				int v = p.first, w = p.second;
				if (cost[u] + w < cost[v]) {
					cost[v] = cost[u] + w;
					parent[v] = u;
					pq.push({cost[v], v});
				}
			}
		}

		cout << "Cheapest routes from " << AIRPORTS[start] << ":" << endl;
		for (int dest = 0; dest < SIZE; dest++) {
			if (dest == start) continue;

			if (cost[dest] >= INF) {
				cout << "No route to " << AIRPORTS[dest] << endl;
				continue;
			}

			vector<int> path;
			for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
			reverse(path.begin(), path.end());

			cout << AIRPORTS[start] << " --> " << AIRPORTS[dest] << " : $" << cost[dest] << " ( ";
			for (int i = 0; i < path.size(); i++) {
				cout << AIRPORTS[path[i]];
				if (i < path.size() - 1) cout << " --> ";
			}
			cout << " )" << endl;
		}
		cout << endl;
	}

	// DFS: list all possible paths from source to destination
	void findAllPaths(int start, int dest) {
		vector<bool> visited(SIZE, false);
		vector<int> path;
		cout << "All possible paths from " << AIRPORTS[start] << " to " << AIRPORTS[dest] << ":" << endl;
		dfsAllPathsUtil(start, dest, visited, path);
		cout << "\n";
	}

	// Minimum Spanning Tree (Prim's Algorithm)
	void minimumSpanningTree() {
		const int INF = 1e9;
		vector<int> key(SIZE, INF);
		vector<int> parent(SIZE, -1);
		vector<bool> inMST(SIZE, false);

		key[0] = 0;

		for (int count = 0; count < SIZE - 1; count++) {
			int u = -1;
			for (int i = 0; i < SIZE; i++)
				if (!inMST[i] && (u == -1 || key[i] < key[u]))
					u = i;

			inMST[u] = true;

			for (auto &p: adjList[u]) {
				int v = p.first, w = p.second;
				if (!inMST[v] && w < key[v]) {
					key[v] = w;
					parent[v] = u;
				}
			}
		}

		cout << "Minimum Spanning Tree:" << endl;
		int total = 0;
		for (int i = 1; i < SIZE; i++) {
			if (parent[i] != -1) {
				cout << AIRPORTS[parent[i]] << " -- " << AIRPORTS[i]
						<< " ($" << key[i] << ")" << endl;
				total += key[i];
			}
		}
		cout << "Total MST Cost: $" << total << endl;
	}

private:
	void dfsAllPathsUtil(int current, int dest, vector<bool> &visited, vector<int> &path) {
		visited[current] = true;
		path.push_back(current);

		if (current == dest) {
			for (int i = 0; i < path.size(); i++) {
				cout << AIRPORTS[path[i]];
				if (i < path.size() - 1) cout << " --> ";
			}
			cout << endl;
		} else {
			for (auto &p: adjList[current]) {
				int neighbor = p.first;
				if (!visited[neighbor]) {
					dfsAllPathsUtil(neighbor, dest, visited, path);
				}
			}
		}

		path.pop_back();
		visited[current] = false;
	}
};

// airportIndex() converts a string into the corresponding index value in the AIRPORTS vector.
// arguments: a string airport name
// output: the index that corresponds with the airport name
int airportIndex(string);

// menu() displays a menu and calls the member functions that correspond with the user's selection on the Graph object
// arguments: a reference to a Graph object
// output: nothing
void menu(Graph &);

int main() {
	// Each edge = (origin airport, destination airport, ticket cost)
	vector<Edge> edges = {
		{0, 1, 200}, {0, 2, 350}, {0, 3, 180},
		{1, 5, 220}, {2, 3, 300}, {2, 4, 250}, {2, 6, 400},
		{4, 7, 150}, {6, 7, 275}, {6, 8, 450},
		{7, 9, 175}, {9, 10, 320}
	};

	Graph graph(edges);

	menu(graph);

	return 0;
}

// Convert airport code (string) to index
int airportIndex(string code) {
	for (int i = 0; i < SIZE; i++) {
		if (AIRPORTS[i] == code)
			return i;
	}
	return -1;
}

// Menu
void menu(Graph &graph) {
	while (true) {
		cout << "===== Airline Route System =====" << endl;
		cout << "1. Show all flights" << endl;
		cout << "2. Get cheapest route from one airport to other airports" << endl;
		cout << "3. Get minimum number of layovers between two airports (BFS)" << endl;
		cout << "4. List reachable airports from an airport (BFS)" << endl;
		cout << "5. List ALL possible paths between two airports (DFS)" << endl;
		cout << "6. Find Minimum Spanning Tree" << endl;
		cout << "7. Exit" << endl;
		cout << "Choose an option: ";

		int choice;
		cin >> choice;
		if (choice == 7) break;

		int a, b;
		switch (choice) {
			case 1:
				graph.printGraph();
				break;
			case 2:
				cout << "Enter source airport: "; {
					string src;
					cin >> src;
					a = airportIndex(src);
					if (a == -1) {
						cout << "Invalid airport code." << endl;
						break;
					}
				};
				graph.cheapestRoutesFrom(a);
				break;
			case 3:
				cout << "Enter source: "; {
					string src, dst;
					cin >> src;
					cout << "Enter destination: ";
					cin >> dst;
					a = airportIndex(src);
					b = airportIndex(dst);
					if (a == -1 || b == -1) {
						cout << "Invalid airport code." << endl;
						break;
					}
				};
				graph.minimumLayovers(a, b);
				break;
			case 4:
				cout << "Enter hub airport: "; {
					string src;
					cin >> src;
					a = airportIndex(src);
					if (a == -1) {
						cout << "Invalid airport code." << endl;
						break;
					}
				};
				graph.reachableAirports(a);
				break;
			case 5:
				cout << "Enter source: "; {
					string src, dst;
					cin >> src;
					cout << "Enter destination: ";
					cin >> dst;
					a = airportIndex(src);
					b = airportIndex(dst);
					if (a == -1 || b == -1) {
						cout << "Invalid airport code." << endl;
						break;
					}
				};
				graph.findAllPaths(a, b);
				break;
			case 6:
				graph.minimumSpanningTree();
				break;
			default:
				cout << "Invalid choice." << endl;
		}
	}
}
