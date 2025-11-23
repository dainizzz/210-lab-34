// COMSC-210 | Lab 34 | Dainiz Almazan
// IDE used: CLion

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 11;

// A lookup table so airport 0 = "ATL", 1 = "LAX", etc.
// You can change these to any airports you want.
vector<string> airports = {
    "ATL", "LAX", "ORD", "DFW", "DEN",
    "JFK", "SEA", "MIA", "PHX", "CLT", "BOS"
};

struct Edge {
    int src, dest, weight;  // weight = ticket cost
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight)); // undirected flights
        }
    }

    // Print adjacency list
    void printGraph() {
        cout << "\nAvailable Flights (Airport → (Destination, Ticket Cost)):\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << airports[i] << " --> ";
            for (Pair v : adjList[i]) {
                cout << "(" << airports[v.first] << ", $" << v.second << ") ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // ---- ITERATIVE DEPTH FIRST SEARCH ----
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> st;

        st.push(start);

        cout << "DFS starting from " << airports[start] << ":\n";

        while (!st.empty()) {
            int v = st.top();
            st.pop();

            if (!visited[v]) {
                cout << airports[v] << " ";
                visited[v] = true;

                // Push neighbors
                for (auto &p : adjList[v]) {
                    int neighbor = p.first;
                    if (!visited[neighbor]) {
                        st.push(neighbor);
                    }
                }
            }
        }

        cout << "\n\n";
    }

    // ---- BREADTH FIRST SEARCH ----
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from " << airports[start] << ":\n";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << airports[v] << " ";

            for (auto &p : adjList[v]) {
                int neighbor = p.first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        cout << "\n\n";
    }
};


int main() {
    // Each edge = (origin airport, destination airport, ticket cost)
    vector<Edge> edges = {
        {0, 1, 200}, {0, 2, 350}, {0, 3, 180},
        {1, 5, 220}, {2, 3, 300}, {2, 4, 250}, {2, 6, 400},
        {4, 7, 150}, {6, 7, 275}, {6, 8, 450},
        {7, 9, 175}, {9, 10, 320}
    };

    Graph graph(edges);

    graph.printGraph();

    graph.DFS(0); // Start DFS from ATL
    graph.BFS(0); // Start BFS from ATL

    return 0;
}
