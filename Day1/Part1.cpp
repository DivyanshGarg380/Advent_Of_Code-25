#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int pos = 50;
	long long count = 0;
	string s;
	while(cin >> s){
		char dir = s[0];
		int x = stoi(s.substr(1));
		if(dir == 'R') {
			pos = (pos+x)%100;
        }else if(dir == 'L'){
            pos = (pos-x)%100;

        }
        if(pos < 0) pos += 100;
		if(pos == 0) count++;
	}
	cout << count ;
}

// Answer : 1036
