#include <iostream>
#include <vector>
#include <stack>

using namespace std;


void dfsRecursive(int v, const vector<vector<int>>& adj, vector<bool>& visited) {
    
    visited[v] = true;
    cout << v << " "; 

    for (int i : adj[v]) {
        if (!visited[i]) {
            dfsRecursive(i, adj, visited);
        }
    }
}


void dfsIterative(int start, const vector<vector<int>>& adj) {
    vector<bool> visited(adj.size(), false);
    stack<int> s;

    
    s.push(start);

    while (!s.empty()) {
       
        int v = s.top();
        s.pop();

        
        if (!visited[v]) {
            visited[v] = true;
            cout << v << " "; 
        }

        
        for (int i : adj[v]) {
            if (!visited[i]) {
                s.push(i);
            }
        }
    }
}

int main() {
    int vn; // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> vn;

    // Create an adjacency list
    vector<vector<int>> adj(vn);

    // Input edges
    int edges;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (format: u v for edge u -> v):" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // Add edge from u to v
    }

    // Perform DFS from vertex 0 using recursion
    cout << "DFS (Recursive) starting from vertex 0:" << endl;
    vector<bool> visited(vn, false);
    dfsRecursive(0, adj, visited);
    cout << endl;

    // Perform DFS from vertex 0 using iteration
    cout << "DFS (Iterative) starting from vertex 0:" << endl;
    dfsIterative(0, adj);
    cout << endl;

    return 0;
}

