#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> G;
vector<bool> visited;

void DFS(int node) {
    visited[node] = true;
    for (int neighbor : G[node]) {
        if (!visited[neighbor]) {
            DFS(neighbor);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if(!(cin >> n >> m)) return 0;
    
    G.resize(n +1);
    visited.resize(n +1, false);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int K_count = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            K_count++;
            DFS(i);
        }
    }

    if (K_count > 0) {
        cout << K_count -1 << "\n";
    } else {
        cout << 0 << "\n";
    }
    return 0;
}