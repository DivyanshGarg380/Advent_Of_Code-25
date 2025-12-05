#include <bits/stdc++.h>
using namespace std;

bool isInvalid(long long n) {
    string s = to_string(n);
    int len = s.length();
    if (len % 2 != 0) return false;
    int half = len / 2;
    for (int i = 0; i < half; i++) {
        if (s[i] != s[i + half]) {
            return false;
        }
    }
    return true; 
}

int main() {
    string input;
    getline(cin, input);
    long long total = 0;
    long long L = 0, R = 0;
    bool readingLeft = true; 
    for (int i = 0; i <= input.size(); i++) {
        if (i == input.size() || input[i] == ',') {
            for (long long x = L; x <= R; x++) {
                if (isInvalid(x)) {
                    total += x;
                }
            }
            L = R = 0;
            readingLeft = true;
        }
        else if (input[i] == '-') {
            readingLeft = false;
        }
        else if (isdigit(input[i])) {
            if (readingLeft) {
                L = L * 10 + (input[i] - '0');
            } else {
                R = R * 10 + (input[i] - '0');
            }
        }
    }
    cout << total;
    return 0;
}

// Ans: 40398804950 