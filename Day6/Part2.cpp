#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> grid;
    string line;

    while (getline(cin, line)) {
        grid.push_back(line);
    }
    if (grid.empty()) return 0;

    int H = grid.size();
    size_t W = 0;

    for (auto &s : grid) W = max(W, s.size());
    for (auto &s : grid) s.resize(W, ' ');

    long long grand_total = 0;
    int col = 0;

    while (col < (int)W) {
        bool all_space = true;
        for (int r = 0; r < H; r++)
            if (grid[r][col] != ' ')
                all_space = false;

        if (all_space) {
            col++;
            continue;
        }

        int start = col;
        int end = col;
        while (end < (int)W) {
            bool all_s = true;
            for (int r = 0; r < H; r++)
                if (grid[r][end] != ' ')
                    all_s = false;
            if (all_s) break;
            end++;
        }

        char op = '?';
        string opcell = grid[H-1].substr(start, end-start);
        if (opcell.find('*') != string::npos) op = '*';
        if (opcell.find('+') != string::npos) op = '+';

        vector<long long> nums;

        for (int c = end-1; c >= start; c--) {
            bool has_digit = false;
            for (int r = 0; r < H-1; r++) {
                if (isdigit(grid[r][c])) {
                    has_digit = true;
                    break;
                }
            }
            if (!has_digit) continue;

            string digits = "";
            for (int r = 0; r < H-1; r++) {
                if (isdigit(grid[r][c]))
                    digits.push_back(grid[r][c]);
            }
            if (!digits.empty())
                nums.push_back(stoll(digits));
        }

        long long result = (op == '*') ? 1 : 0;

        if (op == '*') {
            for (auto v : nums) result *= v;
        } else {
            for (auto v : nums) result += v;
        }

        grand_total += result;

        col = end;
    }

    cout << grand_total << "\n";
    return 0;
}

// Ans: 7329921182115