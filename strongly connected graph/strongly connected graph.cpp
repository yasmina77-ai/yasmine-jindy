#include<iostream>
using namespace std;
class Graph
{
private:
int vertices_num;
int adj_matrix[100][100];// creating adjacency matrix
string state[100];//the state of every verterx
public:
void set_vertices_num(int num) {//set all verteces
	vertices_num = num;
}
void set_ad_matrix(int arr[100][100], int n) {//set adjacency matrix
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			adj_matrix[i][j] = arr[i][j];
	}
}
void print_adj_matrix() {//print the adjacency matrix
	for (int i = 0; i < vertices_num; i++) {
		for (int j = 0; j < vertices_num; j++)
			cout << adj_matrix[i][j] << " ";
		cout << endl;
	}
}
void check_by_dfs(int v_index, bool active[]) {//function to set the state of the nodes that we visited
	active[v_index] = true;
	for (int i = 0; i < vertices_num; i++) {
		if( (adj_matrix[v_index][i]) == 1 && !active[i] )
		check_by_dfs(i, active);
	}
}
bool is_strongly_connected() {//function to check if the Graph is strongly connected
	bool active[100] = { false };
	for (int i = 0; i < vertices_num; i++) {
		for (int j = 0; j < vertices_num; j++)
			active[j] = false;
		check_by_dfs(i, active);
		for (int k = 0; k < vertices_num; k++) {
			if (!active[i])
				return false;
		}
	}
}
};
int main () {

	Graph g;
	int n;
	cout << "Enter number of vertices :";
		cin >> n;
	g.set_vertices_num(n);
	int adj[100][100];
	cout << "Enter the adjacency matrix (only 0 or 1) : " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> adj[i][j];
			if (adj[i][j] != 0 && adj[i][j] != 1) {
				cout << "Enter only 0 or 1" << endl;
				return 1;//end of code when error from user happen
			}
		}
	}
	g.set_ad_matrix(adj, n);
	cout << "Adjacency matrix :" << endl;
	g.print_adj_matrix();
	if (g.is_strongly_connected()) {
		cout << "This graph is strongly connected" << endl;
	}
	else {
		cout << "This graph is not strongly connected" << endl;
	}
	return 0;
}