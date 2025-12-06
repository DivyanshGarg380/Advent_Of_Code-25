#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	vector<string>grid;
	string row;
	while(cin >> row){
		grid.push_back(row);
	}
	int n = grid.size();
	int m = grid[0].size();
	int accessible = 0;
	int dx[8] = {-1,-1,-1,0,0,1,1,1}; // All x coordinates of the 8 positions
	int dy[8] = {-1,0,1,-1,1,-1,0,1}; // All y coordinates of the 8 positions
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(grid[i][j] != '@') continue;
			int count = 0;
			for(int d=0;d<8;d++){
				int ni = i + dx[d];
				int nj = j + dy[d];
				if(ni >= 0 && ni < n && nj >= 0 && nj < m){
					if(grid[ni][nj] == '@') count++;
				}
			}
			if(count < 4) accessible++;
		}
	}
	cout << accessible;
	return 0;
}

// Ans : 1395