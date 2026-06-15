#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
private:
    int n;
    vector<long long> tree;

    void update(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] += val;
            return;
        }
        int mid = (start + end) /2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2* node] + tree[2 * node + 1];
    }
    long long request(int node, int start, int end, int left, int right) {
        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) / 2;
        long long sum_left = request(2 * node, start, mid, left, right);
        long long sum_right = request(2 * node + 1, mid + 1, end, left, right);
        return sum_left + sum_right;
    }
public:
    SegmentTree(int size) {
        n = size;
        tree.assign(4* n,0);
    }
    void add(int idx, long long val) {
        update(1, 1, n, idx, val);
    }
    long long getSum(int left, int right) {
        return request(1, 1, n, left, right);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) {
        return 0;
    }

    SegmentTree st(n);
    for (int i = 0; i < k; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int street;
            long long snow;
            cin >> street >> snow;
            st.add(street, snow);
        } else {
            int u, r_idx;
            cin >> u >> r_idx;
            int left = min(u, r_idx);
            int right = max(u, r_idx);
            cout << st.getSum(left, right) << "\n";
        }
    }
    return 0;
    cout << endl;
}