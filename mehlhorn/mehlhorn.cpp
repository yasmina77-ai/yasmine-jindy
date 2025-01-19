 #include <iostream>
 #include <vector>
 #include <queue>
 #include <set>

 using namespace std;

 struct Edge {
	 int u, v;
	
};

 vector<int> mehlhorn_matching(const vector<int>&L, const vector<int>&R, const vector<Edge>&E) {
	 int n = L.size();
	 int m = R.size();
	 vector<int> matching(n + m, -1);
	 for (int i = 0; i < n; i++) {
		 matching[i] = -1;
		
	}
	 for (int i = 0; i < m; i++) {
		 matching[n + i] = -1;
		
	}
	 for (const Edge& edge : E) {
		 int u = edge.u;
		 int v = edge.v;
		 if (matching[u] == -1 && matching[n + v] == -1) {
			 matching[u] = n + v;
			 matching[n + v] = u;
			
		}
		
	}
	 while (true) {
		 int u = -1;
		 for (int i = 0; i < n; i++) {
			 if (matching[i] == -1) {
				 u = i;
				 break;
				
			}
			
		}
		
			 if (u == -1) {
			 break;
			
		}
		 set<int> visited;
		 queue<int> queue;
		 queue.push(u);
		 vector<int> parent(n + m, -1);
		 bool found_alternating_path = false;
		
			 while (!queue.empty() && !found_alternating_path) {
			 int u = queue.front();
			 queue.pop();
			 visited.insert(u);
			
				 for (const Edge& edge : E) {
				 int v = edge.u;
				 if (u == edge.v) {
					 v = edge.u;
					
				}
				
					 if (!visited.count(v) && (matching[v] == -1 || !visited.count(matching[v]))) {
					 queue.push(v);
					 parent[v] = u;
					 if (matching[v] == -1) {
						 found_alternating_path = true;
						 break;
						
					}
					
				}
				
			}
		}
			 if (found_alternating_path) {
			 int v = n + m - 1;
			 while (parent[v] != -1) {
				 int u = parent[v];
				 int w = matching[u];
				 matching[u] = v;
				 matching[v] = u;
				 v = w;
				
			}
			
		}
			else {
			 int v = -1;
			 for (const Edge& edge : E) {
				 int u = edge.u;
				 if (u == edge.v) {
					 u = edge.u;
					
				}
				
					 if (matching[u] == -1 && !visited.count(v)) {
					 v = u;
					 break;
					
				}
				
			}
			
				 for (int i = 0; i < n; i++) {
				 if (matching[i] != -1 && visited.count(matching[i])) {
					 matching[i] = -1;
					
				}
				
			}
			
				 matching[v] = n + m - 1;
			 matching[n + m - 1] = v;
			
		}
		
	}
	
		 return matching;
	
}

 int main() {
	
		 vector<int> L = { 0, 1, 2, 3 };
	 vector<int> R = { 4, 5, 6, 7 };
	 vector<Edge> E = { {0, 4}, {0, 5}, {1, 5}, {1, 6}, {2, 6}, {2, 7}, {3, 7} };
	
		
		 vector<int> matching = mehlhorn_matching(L, R, E);
	
		 for (int i = 0; i < matching.size(); i++) {
		 if (matching[i] != -1) {
			 cout << i << " matches with " << matching[i] - L.size() << endl;
			
		}
	
	}
	 return 0;

}
