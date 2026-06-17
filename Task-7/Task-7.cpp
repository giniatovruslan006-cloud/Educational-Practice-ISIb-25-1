#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool is_valid_letter(char c) {
    return (c >= 'A' && c <= 'Z');
}

bool is_valid_digit(char c) {
    return isdigit(static_cast<unsigned char>(c));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) {
        return 0;
    }
    if (s.length() != 6) {
        cout << "No" << endl;
        return 0;
    }

    bool is_number = true;
    if (!is_valid_letter(s[0])) {
        is_number = false;
    }
    if (!is_valid_digit(s[1]) || !is_valid_digit(s[2]) || !is_valid_digit(s[3])) {
        is_number = false;
    }
    if (!is_valid_letter(s[4]) || !is_valid_letter(s[5])) {
        is_number = false;
    }

    if (is_number) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;

}