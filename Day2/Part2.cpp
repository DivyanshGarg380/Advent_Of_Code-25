#include <bits/stdc++.h>
using namespace std;

bool isInvalid(long long num) {
    string s = to_string(num);
    int n = s.length();

    // Try all possible block sizes
    for (int block = 1; block <= n / 2; block++) {

        // Only if string length is a multiple of block size
        if (n % block != 0) continue;

        string part = s.substr(0, block);

        bool ok = true;
        // Check if whole string is repeated 'part'
        for (int i = 0; i < n; i++) {
            if (s[i] != part[i % block]) {
                ok = false;
                break;
            }
        }

        if (ok) return true; // invalid
    }

    return false; // not invalid
}

int main() {
    string input;
    getline(cin, input);

    long long total = 0;

    long long L = 0, R = 0;
    bool readingLeft = true;

    for (int i = 0; i <= input.size(); i++) {

        if (i == input.size() || input[i] == ',') {

            // check all numbers in the range
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
            if (readingLeft) L = L * 10 + (input[i] - '0');
            else R = R * 10 + (input[i] - '0');
        }
    }

    cout << total;
    return 0;
}

// Ans: 65794984339

