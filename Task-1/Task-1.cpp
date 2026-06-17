#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0; // Считываем высоту пирамиды

    vector<vector<int>> triangle(n); // Двумерный вектор для хранения исходной пирамиды чисел
    
    // Считываем элементы пирамиды строка за строкой
    for (int i = 0; i < n; ++i) {
        triangle[i].resize(i + 1);
        for (int j = 0; j <= i; ++j) {
            cin >> triangle[i][j];
        }
    }

    vector<vector<int>> dp(n); // Хранит минимальную стоимость пути от элемента (i, j) до самого низа
    vector<vector<int>> next_j(n); // Хранить индекс столбца следующего элемента на оптимальном пути вниз

    // Инициализируем размеры строк для таблиц дп
    for (int i = 0; i < n; ++i) {
        dp[i].resize(i + 1);
        next_j[i].resize(i + 1);
    }

    // Базовый случай (самый нижний ряд пирамиды)
    for (int j = 0; j < n; ++j) {
        dp[n - 1][j] = triangle[n - 1][j];
    }

    // Двигаемся снизу вверх, с предпоследнего ряда
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            
            // Сравниваем, какой путь выгоднее (влево или вправо)
            if (dp[i + 1][j] <= dp[i + 1][j + 1]) {
                dp[i][j] = triangle[i][j] + dp[i + 1][j];
                next_j[i][j] = j;  // Запоминаем путь (j)
            } else {
                dp[i][j] = triangle[i][j] + dp[i + 1][j + 1];
                next_j[i][j] = j + 1;  // Запоминаем путь (j + 1)
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