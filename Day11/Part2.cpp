#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> graph;
map<tuple<string,int,int>, long long> dp;

long long dfs(const string &u, int hasDAC, int hasFFT) {

    int nd = hasDAC || (u == "dac");
    int nf = hasFFT || (u == "fft");

    if (u == "out")
        return (nd && nf) ? 1 : 0;

    auto state = make_tuple(u, nd, nf);
    if (dp.count(state)) return dp[state];

    long long ways = 0;
    for (auto &v : graph[u]) {
        ways += dfs(v, nd, nf);
    }
    return dp[state] = ways;
}

string clean(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' '))
        s.pop_back();
    return s;
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

        string nxt;
        while (ss >> nxt) {
            nxt = clean(nxt);
            graph[name].push_back(nxt);
        }
    }

    cout << dfs("svr", 0, 0) << "\n";
    return 0;
}


// Ans: 533996779677200