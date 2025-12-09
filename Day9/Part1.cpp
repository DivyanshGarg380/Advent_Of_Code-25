#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<pair<long long, long long>> points;
    long long x, y;

    while (scanf("%lld,%lld", &x, &y) == 2) {
        points.push_back({x, y});
    }

    long long maxArea = 0;
    int n = (int)points.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long dx = llabs(points[i].first  - points[j].first);
            long long dy = llabs(points[i].second - points[j].second);

            long long width  = dx + 1;
            long long height = dy + 1;
            long long area   = width * height;

            if (area > maxArea) maxArea = area;
        }
    }

    cout << maxArea << '\n';
    return 0;
}


// Ans: 4759930955