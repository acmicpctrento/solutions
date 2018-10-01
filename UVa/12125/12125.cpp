/******
 * UVa 12125
 *
 * Max Flow using Edmonds-Karp
 */

#include <bits/stdc++.h>
#include <limits.h>
#define MAXN 101
#define MAXV 220

using namespace std;

typedef pair<int, int> ii;
int n, f, penguins, s;
long double d;

//<node no., capacity> - adjacency list
vector<vector<ii>> adj_list(2 * MAXN + 1);
//distance matrix, actually
int adj_matrix[2*MAXN+1][2*MAXN+1], adj_matrix_cpy[2*MAXN+1][2*MAXN+1];
vector<int> p;

inline int dist2 (int x1, int y1, int x2, int y2) {
	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}


void augment(int v, int minEdge) { // traverse BFS spanning tree from s->t
	if (v == s) {
	       f = minEdge;
	       return;
	} // record minEdge in a global var f
	else if (p[v] != -1) {
		augment(p[v], min(minEdge, adj_matrix[p[v]][v]));
		adj_matrix[p[v]][v] -= f;
		adj_matrix[v][p[v]] += f;
	}
}

int main() {
	int ntc;
	cin >> ntc;
	for (int wtf = 0; wtf < ntc; wtf++){
		cin >> n >> d;
		d *= d;
		
		penguins = 0;
		adj_list.clear();
		memset(adj_matrix_cpy, 0, sizeof(adj_matrix));	
		//<x, y>
		vector<ii> positions(n);
		
		for (int i = 0; i < n; i++){
			int x, y, ni, mi;
			cin >> x >> y >> ni >> mi;
			//insert position
			positions[i] = ii(x, y);
			//fake edge for vertex capacity
			adj_list[i].push_back(ii(n + i, mi));
			adj_list[n+1].push_back(ii(i, 0));
			adj_matrix_cpy[i][n+i] = mi;

			//connect supersource
			adj_list[2 * n].push_back(ii(i, ni));
			adj_list[i].push_back(ii(2*n, 0));

			adj_matrix_cpy[2 * n][i] = ni;

			//clear diagonal
			adj_matrix_cpy[i][i] = 0;

			penguins += ni;
		}

		//generate adj list
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				if (dist2 (positions[i].first, positions[i].second, positions[j].first, positions[j].second) <= d + 1e-6) {
					adj_list[n + i].push_back(ii(j, INT_MAX));
					adj_list[n + j].push_back(ii(i, INT_MAX));
					adj_list[j].push_back(ii(n + i, 0));
					adj_list[i].push_back(ii(n + j, 0));
										
					adj_matrix_cpy[n + i][j] = INT_MAX;
					adj_matrix_cpy[n + j][i] = INT_MAX;
				}
			}
		}
#if 0
		//print adj matrix
		int i = 0;
		for (vector<ii> adj: adj_list) {
			cout << "Node " << i++ << ": ";
			for (ii pair: adj) {
				cout << pair.first << "(" << pair.second << ") ";
			}
			cout << endl;
		}
#endif

		//EDMONDS-KARP WEIRDO ALGO
		vector<int> solutions;
		s = 2 * n;
		for (int t = 0; t < n; t++) {
			memcpy(adj_matrix, adj_matrix_cpy, sizeof(adj_matrix));
			int mf = 0;
			while (1) {
				// now a true O(VE^2) Edmonds Karp’s algorithm
				f = 0;
				bitset<MAXV> vis; vis[s] = true;
				// we change vi dist to bitset!
				queue<int> q; q.push(s);
				p.assign(2 * n + 1, -1);
				while (!q.empty()) {
					int u = q.front(); q.pop();
					if (u == t) break;
					for (int j = 0; j < (int)adj_list[u].size(); j++) {
						// AdjList here!
						int v = adj_list[u][j].first;
						// we use vector<vi> AdjList
						if (adj_matrix[u][v] > 0 && !vis[v]) {
							vis[v] = true;
						       	q.push(v);
						       	p[v] = u;
						}
					}
				}
				augment(t, INT_MAX);

				if (f == 0) break;
				mf += f;
			}

			if (mf >= penguins)
				solutions.push_back(t);
		}
		if (solutions.size() == 0)
			cout << -1 << endl;
		else {
			cout << solutions[0];
			for (int i = 1; i<solutions.size(); i++)
				cout << " " << solutions[i];
			cout << endl;
		}
	}
}
