#include<iostream>
using namespace std;
void dfs_bridge(int adj[10][10], int vn, int v, bool visited[], int disc[], int low[], int parent, bool
	& found)//function use dfs algorithm to find bridge
{
	static int time = 0;
	visited[v] = true;
	low[v] = disc[v] = ++time;//disc is discover time of vertex,low is min discover time to access from vertex
		for (int i = 0; i < vn; i++)
		{
			if (adj[v][i] == 1)
			{
				if (!visited[i])// if the vertex has not been visited repeat the procedures
				{
					dfs_bridge(adj, vn, i, visited, disc, low, v, found);
					low[v] = min(low[v], low[i]);
					if (low[i] > disc[v])// if low of neighboring vertex was larger than disc of current vertex then it is a bridge(the edge between v and i)
						found = true;
				}
				else if (i != parent) low[v] = min(low[v], disc[i]);//to know that if vertex was visited
			}
		}
}
bool found_bridge(int adj[10][10], int vn) //function to check if the graph contain bridge or not
{
	for (int i = 0; i < vn; i++)
	{
		for (int j = 0; j < vn; j++)
			if (adj[i][j] == 1) adj[j][i] = 1;
	}// this procedures to convert directed graph to undirected graph
	bool visited[10];
	bool found = false;
	int low[10], disc[10];
	for (int i = 0; i < vn; i++)
	{
		low[i] = disc[i] = -1;
	}
	for (int i = 0; i < vn; i++)
	{
		if (!visited[i])
		{
			dfs_bridge(adj, vn, i, visited, disc, low, -1, found);// if the vertex has not been visited call dfs and if a bridge is found, the procedures stops and returns true
				if (found) return true;
		}
	}
	return false;
}
void dfs(int f, int adj[10][10], int vn, bool visited[])//function to set the state of the vertex that we visited
{
 visited[f] = true;
 for (int i = 0; i < vn; i++)
 {
 if (adj[f][i] == 1 && !visited[i])
 {
 dfs(i,adj,vn,visited);
 }
 }
}
bool issc(int adj[10][10], int vn)//function to check if the graph is sc or not
{
	bool visited[10];
	dfs(0, adj, vn, visited);//to check the connect from front
	for (int i = 0; i < vn; i++)
	{
		if (!visited[i]) return false;
	}
	int revadj[10][10];
	for (int i = 0; i < vn; i++)
	{
		for (int j = 0; j < vn; j++)
			revadj[j][i] = adj[i][j];
	}//create a reveres array
	for (int i = 0; i < vn; i++) visited[i] = false;//reset visited
	dfs(0, revadj, vn, visited);//to check the connect from back
	for (int i = 0; i < vn; i++)
	{
		if (!visited[i]) return false;
	}
	return true;//if all vertix are visited return true
}
bool istcs(int adj[10][10], int vn)// function to check if the graph is tcs or not
{
	if (issc(adj, vn) and !found_bridge(adj, vn))
		return true;
	else return false;
}


