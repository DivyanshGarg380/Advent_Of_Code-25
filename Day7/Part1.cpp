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

    queue<pair<int,int>> q;
    vector<vector<bool>> vis(H, vector<bool>(W, false));
    q.push({sr, sc});
    vis[sr][sc] = true;

    long long splits = 0;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        int nr = r + 1, nc = c;

        if (nr >= H) continue;
        char ch = g[nr][nc];

        if (ch == '.') {
            if (!vis[nr][nc]) {
                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        } else if (ch == '^') {
            splits++;
            int lr = nr, lc = nc - 1;
            int rr = nr, rc = nc + 1;
            if (lc >= 0 && !vis[lr][lc]) {
                vis[lr][lc] = true;
                q.push({lr, lc});
            }
            if (rc < W && !vis[rr][rc]) {
                vis[rr][rc] = true;
                q.push({rr, rc});
            }
        }
    }

    cout << splits << "\n";
}

// Ans: 1667