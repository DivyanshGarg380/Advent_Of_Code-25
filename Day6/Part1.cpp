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
    size_t W = 0;
    for (auto &s : grid) W = max(W, s.size());
    for (auto &s : grid) s.resize(W, ' ');

    int H = grid.size();

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
        while (end < W) {
            bool all_s = true;
            for (int r = 0; r < H; r++)
                if (grid[r][end] != ' ')
                    all_s = false;
            if (all_s) break;
            end++;
        }

        vector<long long> nums;
        char op = '?';

        for (int r = 0; r < H; r++) {
            string cell = grid[r].substr(start, end - start);

            if (cell.find('*') != string::npos) {
                op = '*';
                continue;
            }
            if (cell.find('+') != string::npos) {
                op = '+';
                continue;
            }

            string t;
            for (char c : cell)
                if (isdigit(c)) t.push_back(c);

            if (!t.empty())
                nums.push_back(stoll(t));
        }

        long long result = (op == '*') ? 1 : 0;

        if (op == '*') {
            for (long long v : nums) result *= v;
        } else if (op == '+') {
            for (long long v : nums) result += v;
        }

        grand_total += result;

        col = end; 
    }

    cout << grand_total << "\n";
    return 0;
}

// Ans: 4648618073226