#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int k;

    if(!(cin >> n >> k)) {
        return 0;
    }

    vector<int> P(n);
    for (int i = 0; i < n; ++i) {
        cin >> P[i];
        P[i]--;
    }
    string cypher;
    cin >> cypher;
    
    vector<int> inv_P(n);
    for (int i = 0; i < n; ++i) {
        inv_P[P[i]] = i;
    }

    string text(n, ' ');
    vector<bool> visited(n, false);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> cycle;
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                cycle.push_back(curr);
                curr = inv_P[curr];
            }
            int cycle_len = cycle.size();
            
            for (int j = 0; j < cycle_len; ++j) {
                int idx = cycle[(j + (k % cycle_len)) % cycle_len];
                text[cycle[j]] = cypher[idx];
            }
        }
    }
    cout << text << endl;
    return 0;
}