
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Function to perform DFS
void dfs(int v, const vector<vector<int>>&adj, vector<bool>&visited) {
    visited[v] = true;
    for (int i = 0; i < adj[v].size(); i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            dfs(i, adj, visited);
        }
    }
}

// Function to create the transpose of the graph
vector<vector<int>> transposeGraph(const vector<vector<int>>&adj) {
    int vn = adj.size();
    vector<vector<int>> transposed(vn, vector<int>(vn, 0));

    for (int i = 0; i < vn; i++) {
        for (int j = 0; j < vn; j++) {
            transposed[j][i] = adj[i][j]; // Reverse the direction of edges
        }
    }

    return transposed;
}

// Function to check if the graph is strongly connected
bool isStronglyConnected(const vector<vector<int>>&adj) {
    int vn = adj.size();
    vector<bool> visited(vn, false);

    // Step 1: Perform DFS from the first vertex
    dfs(0, adj, visited);

    // Check if all vertices were visited
    for (bool v : visited) {
        if (!v) return false; // Not all vertices are reachable
    }

    // Step 2: Create the transposed graph
    vector<vector<int>> transposed = transposeGraph(adj);

    // Reset visited array for the second DFS
    fill(visited.begin(), visited.end(), false);

    // Perform DFS on the transposed graph
    dfs(0, transposed, visited);

    // Check if all vertices were visited in the transposed graph
    for (bool v : visited) {
        if (!v) return false; // Not all vertices are reachable in the transposed graph
    }

    return true; // The graph is strongly connected
}

int main() {
    int vn;
    cout << "Enter the number of vertices: ";
    cin >> vn;

    // Create an adjacency matrix initialized to 0
    vector<vector<int>> adj(vn, vector<int>(vn, 0));

    // Input edges
    cout << "Enter the adjacency matrix (enter 1 for edge, 0 for no edge):" << endl;
    for (int i = 0; i < vn; i++) {
        for (int j = 0; j < vn; j++) {
            cin >> adj[i][j];
        }
    }

    // Check if the graph is strongly connected
    if (isStronglyConnected(adj)) {
        cout << "The graph is strongly connected." << endl;
    }
    else {
        cout << "The graph is not strongly connected." << endl;
    }

    return 0;
}