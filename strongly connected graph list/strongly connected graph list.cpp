#include <iostream>
#include <list>
using namespace std;

list<int> adList[100];
void addEdge(int u, int v) {
	adList[u].push_back(v);
}
void DFS(int v, bool getit[], int V) {
	getit[v] = true;
	for (int neighbor : adList[v]) {
		if (!getit[neighbor]) {
			DFS(neighbor, getit, V);
		}
	}
}
void getOpp(int V) {
	list<int> adListOpp[100];
	for (int u = 0; u < V; u++) {
		for (int v : adList[u]) {
			adListOpp[v].push_back(u);
		}
	}

	for (int i = 0; i < V; i++) {
		adList[i] = adListOpp[i];
	}
}
bool isStronglyConnected(int V) {
	bool getit[100] = { false };
	DFS(0, getit, V);
	for (int i = 0; i < V; i++) {
		if (!getit[i]) {
			return false;
		}
	}
	getOpp(V);
	fill(getit, getit + V, false);
	DFS(0, getit, V);
	for (int i = 0; i < V; i++) {
		if (!getit[i]) {
			return false;
		}
	}
	return true;
}