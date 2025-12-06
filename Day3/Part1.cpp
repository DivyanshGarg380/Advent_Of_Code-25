#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	string s;
    long long total = 0;
    while (cin >> s) {   
        int n = s.size();
        int best = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int tens = s[i] - '0';
                int ones = s[j] - '0';
                int val = tens * 10 + ones;
                best = max(best, val);
            }
        }
        total += best;
    }
    cout << total;
	return 0;
}
// Can be optimized further by using Greedy approach :)
// Ans: 17179