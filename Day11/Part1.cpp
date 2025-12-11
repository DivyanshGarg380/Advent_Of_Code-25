#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> graph;
unordered_map<string, long long> memo;

string clean(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' '))
        s.pop_back();
    return s;
}

long long dfs(string node) {
    if (node == "out") return 1;
    if (memo.count(node)) return memo[node];

    long long ways = 0;
    for (auto &nx : graph[node]) {
        ways += dfs(nx);
    }
    return memo[node] = ways;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name;
        ss >> name;

        if (!name.empty() && name.back() == ':')
            name.pop_back();

        name = clean(name);

        string dst;
        while (ss >> dst) {
            dst = clean(dst);
            graph[name].push_back(dst);
        }
    }

    cout << dfs("you") << "\n";
    return 0;
}

// Ans: 683