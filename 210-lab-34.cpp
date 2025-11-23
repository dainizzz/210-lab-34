// COMSC-210 | Lab 34 | Dainiz Almazan
// IDE used: CLion

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 11;

// A lookup table so airport 0 = "ATL", 1 = "LAX", etc.
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
        cout << "\nAvailable Flights (Airport --> (Destination, Ticket Cost)):\n";
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



    // BFS for minimum layovers
    void minimumLayovers(int start, int dest) {
        vector<bool> visited(SIZE, false);
        vector<int> dist(SIZE, -1);
        queue<int> q;


        visited[start] = true;
        dist[start] = 0;
        q.push(start);


        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &p : adjList[v]) {
                int neighbor = p.first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    dist[neighbor] = dist[v] + 1;
                    q.push(neighbor);
                }
            }
        }


        cout << "\nMinimum layovers from " << airports[start] << " to " << airports[dest] << ": ";
        if (dist[dest] == -1) cout << "No route available.";
        else cout << dist[dest] << " layovers.";
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

    cout << "Exploring possible flight paths from ATL..." << endl;
    graph.DFS(0); // Start DFS from ATL
    cout << "Exploring flights with the fewest layovers (BFS) from ATL to BOS..." << endl;
    graph.minimumLayovers(0,10); // Start BFS from ATL

    return 0;
}
