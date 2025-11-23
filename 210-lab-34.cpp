// COMSC-210 | Lab 34 | Dainiz Almazan
// IDE used: CLion

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    vector<vector<Pair>> adjList;

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
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // ---- DEPTH FIRST SEARCH ----
    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        // Visit all neighbors
        for (auto &p : adjList[v]) {
            int neighbor = p.first;
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        cout << "DFS traversal starting from " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // ---- BREADTH FIRST SEARCH ----
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from " << start << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            // Visit neighbors
            for (auto &p : adjList[v]) {
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
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},
        {5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    Graph graph(edges);

    graph.printGraph();

    cout << endl;
    graph.DFS(0);   // start DFS at node 0
    graph.BFS(0);   // start BFS at node 0

    return 0;
}

