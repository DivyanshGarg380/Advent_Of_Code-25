#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<pair<long long, long long>> ranges;
    vector<long long> ids;

    string line;

    while (getline(cin, line)) {
        if (line.size() == 0) break;
        long long a, b;
        sscanf(line.c_str(), "%lld-%lld", &a, &b);
        ranges.push_back({a, b});
    }

    while (getline(cin, line)) {
        if (line.size() == 0) continue;
        ids.push_back(stoll(line));
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

    int fresh = 0;
    for (long long x : ids) {
        // taking o(nlogn) approach to avoid TLE :)
        int l = 0, h = merged.size() - 1;
        bool ok = false;

        while (l <= h) {
            int m = (l + h) / 2;
            if (merged[m].first <= x && x <= merged[m].second) {
                ok = true;
                break;
            }
            if (x < merged[m].first) h = m - 1;
            else l = m + 1;
        }
        if (ok) fresh++;
    }

    cout << fresh << "\n";
    return 0;
}


// Ans: 712