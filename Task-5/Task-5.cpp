#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w;
    if (!(cin >> h >> w)) {
        return 0;
    }

    int min_row = h, max_row = -1;
    int min_col = w, max_col = -1;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int value;
            cin >> value;

            if (value == 1) {
                min_row = min(min_row, i);
                max_row = max(max_row, i);
                min_col = min(min_col, j);
                max_col = max(max_col, j);
            }
        }
    }

    int rect_top_row = min_row - 1;
    int rect_left_col = min_col - 1;
    int rect_bot_row = max_row + 1;
    int rect_right_col = max_col + 1;

    cout << rect_top_row << " " << rect_left_col << " " << rect_bot_row << " " << rect_right_col << endl;
    return 0;
}