#include <bits/stdc++.h>
using namespace std;

int patternToMask(const string &s) {
    int mask = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#')
            mask |= (1 << i);
    }
    return mask;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    long long totalPresses = 0;

    while (true) {
        getline(cin, line);
        if (!cin) break;
        if (line.size() == 0) continue;

        int lbr = line.find('[');
        int rbr = line.find(']');
        string pattern = line.substr(lbr + 1, rbr - lbr - 1);
        int targetMask = patternToMask(pattern);
        int nLights = pattern.size();

        vector<int> buttons;
        for (int i = rbr + 1; i < line.size();) {
            if (line[i] == '(') {
                int j = i + 1;
                vector<int> indices;
                int num = 0;
                bool readingNumber = false;

                while (j < line.size() && line[j] != ')') {
                    if (isdigit(line[j])) {
                        readingNumber = true;
                        num = num * 10 + (line[j] - '0');
                    } else {
                        if (readingNumber) {
                            indices.push_back(num);
                            num = 0;
                        }
                        readingNumber = false;
                    }
                    j++;
                }
                if (readingNumber) indices.push_back(num);

                int mask = 0;
                for (int k : indices) mask |= (1 << k);
                buttons.push_back(mask);

                i = j + 1;
            } else {
                i++;
            }
        }

        int B = buttons.size();
        int best = INT_MAX;

        for (int mask = 0; mask < (1 << B); mask++) {
            int current = 0;
            int presses = __builtin_popcount(mask);

            if (presses >= best) continue;

            for (int b = 0; b < B; b++) {
                if (mask & (1 << b)) {
                    current ^= buttons[b];
                }
            }
            if (current == targetMask) {
                best = presses;
            }
        }

        totalPresses += best;
    }

    cout << totalPresses << "\n";
    return 0;
}

// Ans: 449