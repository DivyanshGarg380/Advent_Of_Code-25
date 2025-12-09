#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> g;
    string s;
    while (getline(cin, s)) g.push_back(s);
    int H = g.size(), W = g[0].size();

    int sr = 0, sc = -1;
    for (int c = 0; c < W; c++) if (g[0][c] == 'S') sc = c;

    vector<vector<long long>> dp(H, vector<long long>(W, 0));
    dp[sr][sc] = 1;

    for (int r = sr; r < H; r++) {
        for (int c = 0; c < W; c++) {
            long long ways = dp[r][c];
            if (ways == 0) continue;

            int nr = r + 1;
            if (nr >= H) continue;
            char ch = g[nr][c];

            if (ch == '.') dp[nr][c] += ways;
            else if (ch == '^') {
                if (c - 1 >= 0) dp[nr][c - 1] += ways;
                if (c + 1 < W) dp[nr][c + 1] += ways;
            }
        }
    }

    long long ans = 0;
    for (int c = 0; c < W; c++) ans += dp[H - 1][c];
    cout << ans << "\n";
}


// Ans: 62943905501815