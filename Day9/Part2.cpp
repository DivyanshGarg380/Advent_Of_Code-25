// Part2_fast_fixed.cpp
// C++11 compatible compressed sweep-line solution for AoC Day 9 Part 2

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// flood fill exterior on compressed cell grid (H x W), grid: 0=unknown, 1=boundary, after fill
void bfs_fill(vector< vector<unsigned char> > &grid, int H, int W) {
    vector< vector<unsigned char> > vis(H, vector<unsigned char>(W, 0));
    deque< pair<int,int> > dq;
    auto try_push = [&](int r,int c){
        if(r<0 || r>=H || c<0 || c>=W) return;
        if(vis[r][c]) return;
        if(grid[r][c] == 1) return; // boundary blocks
        vis[r][c] = 1;
        dq.emplace_back(r,c);
    };
    for(int c=0;c<W;++c){ try_push(0,c); try_push(H-1,c); }
    for(int r=0;r<H;++r){ try_push(r,0); try_push(r,W-1); }

    static int dr[4] = {1,-1,0,0};
    static int dc[4] = {0,0,1,-1};
    while(!dq.empty()){
        pair<int,int> p = dq.front(); dq.pop_front();
        int rr = p.first, cc = p.second;
        for(int k=0;k<4;++k){
            int nr = rr + dr[k], nc = cc + dc[k];
            if(nr<0||nr>=H||nc<0||nc>=W) continue;
            if(vis[nr][nc]) continue;
            if(grid[nr][nc] == 1) continue;
            vis[nr][nc] = 1;
            dq.emplace_back(nr,nc);
        }
    }
    // mark interior cells (not visited and not boundary) as 1 (good)
    for(int r=0;r<H;++r)
        for(int c=0;c<W;++c)
            if(!vis[r][c] && grid[r][c] == 0)
                grid[r][c] = 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read red points (x,y) lines
    vector<pair<ll,ll>> R;
    string line;
    while(getline(cin, line)){
        if(line.empty()) continue;
        size_t comma = line.find(',');
        if(comma==string::npos) continue;
        ll x = atoll(line.substr(0, comma).c_str());
        ll y = atoll(line.substr(comma+1).c_str());
        R.emplace_back(x,y);
    }

    int N = (int)R.size();
    if(N < 2){ cout << 0 << "\n"; return 0; }

    // Build compression coordinates: we collect boundaries (coordinate values)
    // For correct interval representation we add both v and v+1 for each integer coordinate used on edges/vertices.
    vector<ll> xs, ys;
    xs.reserve(N*4);
    ys.reserve(N*4);

    for(int i=0;i<N;++i){
        ll x = R[i].first, y = R[i].second;
        xs.push_back(x);
        xs.push_back(x+1);    // boundary of tile cell
        ys.push_back(y);
        ys.push_back(y+1);
    }

    // Also consider segments endpoints: include both endpoints and endpoint+1
    for(int i=0;i<N;++i){
        ll x1 = R[i].first, y1 = R[i].second;
        ll x2 = R[(i+1)%N].first, y2 = R[(i+1)%N].second;
        if(x1 == x2){
            // vertical segment spans y in [minY, maxY]
            ll low = min(y1, y2), high = max(y1,y2);
            ys.push_back(low); ys.push_back(high+1);
            xs.push_back(x1); xs.push_back(x1+1);
        } else if(y1 == y2){
            ll low = min(x1,x2), high = max(x1,x2);
            xs.push_back(low); xs.push_back(high+1);
            ys.push_back(y1); ys.push_back(y1+1);
        } else {
            // shouldn't happen per problem
        }
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    // We will treat compressed cells as intervals [xs[i], xs[i+1]) x [ys[j], ys[j+1])
    if(xs.size() < 2 || ys.size() < 2){
        cout << 0 << "\n";
        return 0;
    }
    int W = (int)xs.size() - 1;
    int H = (int)ys.size() - 1;

    // Maps: to find the cell index that contains coordinate v, use:
    // idx = upper_bound(xs.begin(), xs.end(), v) - xs.begin() - 1
    auto cellX = [&](ll v)->int{
        int idx = int(upper_bound(xs.begin(), xs.end(), v) - xs.begin()) - 1;
        if(idx < 0) idx = 0;
        if(idx >= W) idx = W-1;
        return idx;
    };
    auto cellY = [&](ll v)->int{
        int idx = int(upper_bound(ys.begin(), ys.end(), v) - ys.begin()) - 1;
        if(idx < 0) idx = 0;
        if(idx >= H) idx = H-1;
        return idx;
    };

    // grid: H rows, W cols; 0 = unknown, 1 = boundary (red) or filled later interior
    vector< vector<unsigned char> > grid(H, vector<unsigned char>(W, 0));

    // Mark polygon boundary: for each edge mark all cells whose area intersects the segment
    for(int i=0;i<N;++i){
        ll x1 = R[i].first, y1 = R[i].second;
        ll x2 = R[(i+1)%N].first, y2 = R[(i+1)%N].second;
        if(x1 == x2){
            // vertical line at x = x1, y from low..high inclusive
            ll low = min(y1,y2), high = max(y1,y2);
            int cx = cellX(x1);                 // column containing x1
            // determine row range: cells that intersect [low, high]
            int ry1 = cellY(low);
            int ry2 = cellY(high);
            for(int r = ry1; r <= ry2; ++r) grid[r][cx] = 1;
        } else if(y1 == y2){
            // horizontal line at y = y1, x from low..high
            ll low = min(x1,x2), high = max(x1,x2);
            int cy = cellY(y1);
            int cx1 = cellX(low);
            int cx2 = cellX(high);
            for(int c = cx1; c <= cx2; ++c) grid[cy][c] = 1;
        } else {
            // shouldn't happen
            // ignore
        }
    }

    // Flood-fill exterior and mark interior as good (1)
    bfs_fill(grid, H, W);

    // Build prefix-sum over grid (1 = red or green)
    vector< vector<int> > pref(H+1, vector<int>(W+1, 0));
    for(int r=0;r<H;++r){
        int rowsum = 0;
        for(int c=0;c<W;++c){
            rowsum += (grid[r][c] ? 1 : 0);
            pref[r+1][c+1] = pref[r][c+1] + rowsum;
        }
    }

    auto sumRect = [&](int r1,int c1,int r2,int c2)->int{
        if(r2 < r1 || c2 < c1) return 0;
        return pref[r2+1][c2+1] - pref[r1][c2+1] - pref[r2+1][c1] + pref[r1][c1];
    };

    // Precompute widths and heights of each compressed column/row
    vector<ll> dx(W), dy(H);
    for(int i=0;i<W;i++) dx[i] = xs[i+1] - xs[i];
    for(int j=0;j<H;j++) dy[j] = ys[j+1] - ys[j];

    // Map red tile coordinates to compressed cell indices for corners
    vector< pair<int,int> > RC(N);
    for(int i=0;i<N;++i){
        RC[i].first = cellX(R[i].first);
        RC[i].second = cellY(R[i].second);
    }

    ll best = 0;

    // Iterate all red pairs (i<j) and test rectangle (cells inclusive)
    for(int i=0;i<N;++i){
        int cx1 = RC[i].first, cy1 = RC[i].second;
        for(int j=i+1;j<N;++j){
            int cx2 = RC[j].first, cy2 = RC[j].second;
            if(cx1 == cx2 || cy1 == cy2) continue; // need opposite corners
            int lx = min(cx1, cx2), rx = max(cx1, cx2);
            int ly = min(cy1, cy2), ry = max(cy1, cy2);
            int cells = (rx - lx + 1) * (ry - ly + 1);
            int good = sumRect(ly, lx, ry, rx);
            if(good != cells) continue;
            // compute true area = sum widths * sum heights
            ll width = 0, height = 0;
            for(int c=lx;c<=rx;c++) width += dx[c];
            for(int r=ly;r<=ry;r++) height += dy[r];
            ll area = width * height;
            if(area > best) best = area;
        }
    }

    cout << best << "\n";
    return 0;
}

// Ans: 1525241870