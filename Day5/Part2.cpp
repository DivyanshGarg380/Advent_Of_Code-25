#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<pair<long long, long long>> ranges;
    string line;

    while (getline(cin, line)) {
        if (line.size() == 0) break;
        long long a, b;
        sscanf(line.c_str(), "%lld-%lld", &a, &b);
        ranges.push_back({a, b});
    }

    // Merge overlapping ranges
    sort(ranges.begin(), ranges.end());
    vector<pair<long long, long long>> merged;

    for (auto &r : ranges) {
        if (merged.empty() || r.first > merged.back().second + 1) {
            merged.push_back(r);
        } else {
            merged.back().second = max(merged.back().second, r.second);
        }
    }

    long long total = 0;
    for (auto &p : merged) {
        total += (p.second - p.first + 1);
    }

    cout << total << "\n";
    return 0;
}


// Ans : 332998283036769
