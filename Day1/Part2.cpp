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
		for(int i=0; i<x; i++){
			if(dir == 'R') {
				pos = (pos+1)%100;
			}else if(dir == 'L'){
				pos = (pos-1)%100;
				if(pos < 0) pos += 100;
			}
			if(pos == 0) count++;
		}
	}
	cout << count ;
}

// Answer : 6228
