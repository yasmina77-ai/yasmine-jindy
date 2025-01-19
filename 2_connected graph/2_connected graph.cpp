#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

class Graph {
private:
    int numVertices;
    vector<pair<int, int>> edges;
    vector<vector<int>> adjList;


    void buildAdjList() {
        adjList.assign(numVertices, vector<int>());
        for (auto& edge : edges) {
            adjList[edge.first].push_back(edge.second);
            adjList[edge.second].push_back(edge.first);
        }
    }
    bool isConnected(int ignoreNode = -1) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        int startNode = -1;
        for (int i = 0; i < numVertices; i++) {
            if (i != ignoreNode) {
                startNode = i;
                break;
            }
        }

        if (startNode == -1) return false;

        visited[startNode] = true;
        q.push(startNode);
        int visitedCount = 1;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor] && neighbor != ignoreNode) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    visitedCount++;
                }
            }
        }

        return visitedCount == numVertices - (ignoreNode != -1 ? 1 : 0);
    }
    bool isEdgeConnected() {
        for (auto& edge : edges) {
            buildAdjList();

            adjList[edge.first].erase(
                remove(adjList[edge.first].begin(), adjList[edge.first].end(), edge.second),
                adjList[edge.first].end()
            );
            adjList[edge.second].erase(
                remove(adjList[edge.second].begin(), adjList[edge.second].end(), edge.first),
                adjList[edge.second].end()
            );

            if (!isConnected()) {
                return false;
            }
        }
        return true;
    }

    bool isVertexConnected() {
        for (int i = 0; i < numVertices; i++) {
            buildAdjList();

            if (!isConnected(i)) {
                return false;
            }
        }
        return true;
    }

public:

    Graph(int vertices, vector<pair<int, int>> edgesInput) : numVertices(vertices), edges(edgesInput) {
        buildAdjList();
    }
    string checkConnectivity() {
        bool edgeConnected = isEdgeConnected();
        bool vertexConnected = isVertexConnected();

        if (edgeConnected && vertexConnected || vertexConnected ) {
            return "2_connected graph \n";
        }
      
        else if (edgeConnected) {
            return "2_edges connected";
        }
        else {
            return "graph is not 2_connected";
        }
    }
};

int main() {
    int numVertices = 5;
    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {1, 3}
    };

    Graph graph(numVertices, edges);
    cout << graph.checkConnectivity() << endl;

    return 0;
}
