#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<int> results(n);

    for (int i = 0; i < n; ++i) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        int pairs2 = min(a, y);
        int a_left = a - pairs2;
        int left_for_type1 = a_left + b;
        int pairs1 = min(left_for_type1, x);
        results[i] = pairs2 + pairs1;
    }

    for (int i = 0; i < n; ++i) {
        cout << results[i];
        if (i < n - 1) {
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}