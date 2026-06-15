#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> triangle(n);
    
    for (int i = 0; i < n; ++i) {
        triangle[i].resize(i + 1);
        for (int j = 0; j <= i; ++j) {
            cin >> triangle[i][j];
        }
    }

    vector<vector<int>> dp(n);
    vector<vector<int>> next_j(n);

    for (int i = 0; i < n; ++i) {
        dp[i].resize(i + 1);
        next_j[i].resize(i + 1);
    }

    for (int j = 0; j < n; ++j) {
        dp[n - 1][j] = triangle[n - 1][j];
    }

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            
            if (dp[i + 1][j] <= dp[i + 1][j + 1]) {
                dp[i][j] = triangle[i][j] + dp[i + 1][j];
                next_j[i][j] = j;
            } else {
                dp[i][j] = triangle[i][j] + dp[i + 1][j + 1];
                next_j[i][j] = j + 1;
            }
        }
    }

    cout << dp[0][0] << "\n";


    int current_j = 0;
    for (int i = 0; i < n; ++i) {
        cout << triangle[i][current_j];
        
        if (i < n - 1) {
            cout << " ";
            current_j = next_j[i][current_j];
        }
    }
    cout << "\n";

    return 0;
}