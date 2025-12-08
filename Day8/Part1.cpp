#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> parent, sz;
    DSU(int n) : n(n), parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
    int size(int x) {
        return sz[find(x)];
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
            if (!getline(ss, s, ',')) return 0; 
            p[i] = stoll(s);
        }
        pts.push_back(p);
    }

    int n = (int)pts.size();
    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    vector<Edge> edges;
    edges.reserve(1LL * n * (n - 1) / 2);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = pts[i][0] - pts[j][0];
            long long dy = pts[i][1] - pts[j][1];
            long long dz = pts[i][2] - pts[j][2];
            long long d2 = dx*dx + dy*dy + dz*dz;
            edges.push_back({d2, i, j});
        }
    }

    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b) {
             return a.d2 < b.d2;
         });

    DSU dsu(n);
    const int K = 1000;
    int limit = min((int)edges.size(), K);

    for (int i = 0; i < limit; ++i) {
        dsu.unite(edges[i].u, edges[i].v);
    }

    vector<long long> sizes;
    sizes.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (dsu.find(i) == i) {
            sizes.push_back(dsu.sz[i]);
        }
    }

    sort(sizes.begin(), sizes.end(), greater<long long>());

    long long ans = 1;
    int take = min(3, (int)sizes.size());
    for (int i = 0; i < take; ++i) {
        ans *= sizes[i];
    }

    cout << ans << "\n";
    return 0;
}


// Ans: 24360 