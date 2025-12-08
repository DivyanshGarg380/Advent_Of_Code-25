#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) : parent(n), sz(n,1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; 
        if (sz[a] < sz[b]) swap(a,b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

struct Edge {
    long long d2;
    int u, v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<array<long long, 3>> pts;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string s;
        array<long long, 3> p;
        for (int i = 0; i < 3; ++i) {
            getline(ss, s, ',');
            p[i] = stoll(s);
        }
        pts.push_back(p);
    }
    int n = pts.size();

    vector<Edge> edges;
    edges.reserve(1LL * n * (n-1) / 2);

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            long long dx = pts[i][0] - pts[j][0];
            long long dy = pts[i][1] - pts[j][1];
            long long dz = pts[i][2] - pts[j][2];
            long long d2 = dx*dx + dy*dy + dz*dz;
            edges.push_back({d2, i, j});
        }
    }

    sort(edges.begin(), edges.end(),
        [](auto &a, auto &b){ return a.d2 < b.d2; });

    DSU dsu(n);
    int components = n;

    long long answer = 0;

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            components--;
            if (components == 1) {
                long long x1 = pts[e.u][0];
                long long x2 = pts[e.v][0];
                answer = x1 * x2;
                break;
            }
        }
    }

    cout << answer << "\n";
    return 0;
}


// Ans: 2185817796