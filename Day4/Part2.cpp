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
	vector<vector<int>>cnt(n,vector<int>(m,0)); // to store counts
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
			cnt[i][j] = count;			
		}
	}
	// bakchodi starts here :0
	queue<pair<int,int>>q;
	for(int i=0; i<n; i++){
		for(int j=0;j<m;j++){
			if(grid[i][j] == '@' and cnt[i][j] < 4){
				q.push({i,j});
				grid[i][j] = '#'; // marked for removal for later
			}
		}
	}
	int removed = 0;
	while(!q.empty()){
		auto[x,y] = q.front();q.pop();
		removed++;
		// reduce neighbour counts
		for(int d=0;d<8;d++){
			int nx = x + dx[d];
			int ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '@'){
				cnt[nx][ny]--;
				if(cnt[nx][ny] < 4){
					q.push({nx,ny});
					grid[nx][ny] = '#';
				}
			}
		}
	}
	cout << removed;
	return 0;
}

// Ans : 8451