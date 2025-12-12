#include <bits/stdc++.h>
using namespace std;

string encode(const vector<int> &v) {
    string s;
    for (int x : v) s += to_string(x) + ",";
    return s;
}

struct Node {
    vector<int> s;
    int dist;
    Node(const vector<int>& _s, int _d) : s(_s), dist(_d) {}
};

struct Cmp {
    bool operator()(const Node &a, const Node &b) const {
        return a.dist > b.dist;
    }
};

int solve_machine(const vector<vector<int>> &buttons, const vector<int> &target) {
    int n = target.size();
    vector<int> start(n, 0);

    priority_queue<Node, vector<Node>, Cmp> pq;
    unordered_set<string> seen;

    pq.push(Node(start, 0));
    seen.insert(encode(start));

    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();

        vector<int> cur = top.s;
        int d = top.dist;

        if (cur == target) return d;

        for (auto &btn : buttons) {
            vector<int> nxt = cur;
            bool ok = true;

            for (int idx : btn) {
                nxt[idx]++;
                if (nxt[idx] > target[idx]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            string key = encode(nxt);
            if (seen.count(key)) continue;

            seen.insert(key);
            pq.push(Node(nxt, d + 1));
        }
    }

    return -1; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    long long total = 0;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        vector<int> target;
        vector<vector<int>> buttons;

        // parse target {...}
        {
            size_t L = line.find('{');
            size_t R = line.find('}');
            string inside = line.substr(L + 1, R - L - 1);
            stringstream ss(inside);
            int x; char c;
            while (ss >> x) {
                target.push_back(x);
                ss >> c;
            }
        }

        // parse button lists (...)
        for (int i = 0; i < (int)line.size(); i++) {
            if (line[i] == '(') {
                int j = i + 1;
                while (j < (int)line.size() && line[j] != ')') j++;
                string inside = line.substr(i + 1, j - i - 1);

                vector<int> btn;
                stringstream ss(inside);
                int x; char c;
                while (ss >> x) {
                    btn.push_back(x);
                    ss >> c;
                }
                buttons.push_back(btn);
                i = j;
            }
        }

        total += solve_machine(buttons, target);
    }

    cout << total << "\n";
    return 0;
}
