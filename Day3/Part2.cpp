#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    long long total = 0;
    const int K = 12;

    while (cin >> s) {
        int n = s.size();
        int remove = n - K; 
        string st = "";
        for (char c : s) {
            while (!st.empty() && st.back() < c && remove > 0) {
                st.pop_back();
                remove--;
            }
            st.push_back(c);
        }
        st.resize(K);
        unsigned long long val = stoull(st);
        total += val;
    }

    cout << total;
}
// Optimized using a greedy approach
// Ans : 170025781683941