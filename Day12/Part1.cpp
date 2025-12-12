#include <bits/stdc++.h>
using namespace std;

// Normalize shape coords (shift to origin, sort)
vector<pair<int,int>> norm(const vector<pair<int,int>> &v){
    int minx=1e9,miny=1e9;
    for(auto&p:v){ minx=min(minx,p.first); miny=min(miny,p.second); }
    vector<pair<int,int>> r;
    for(auto&p:v) r.push_back({p.first-minx,p.second-miny});
    sort(r.begin(),r.end());
    return r;
}

// Rotate 90 deg
pair<int,int> rot(pair<int,int> p){ return {p.second, -p.first}; }

vector<vector<pair<int,int>>> genAllVariants(const vector<pair<int,int>>& shape){
    vector<vector<pair<int,int>>> res;
    set<vector<pair<int,int>>> seen;
    for(int flip=0; flip<2; flip++){
        for(int r=0; r<4; r++){
            vector<pair<int,int>> cur = shape;
            // rotate r times
            for(int i=0;i<r;i++)
                for(auto &p:cur) p = rot(p);
            // flip horizontally
            if(flip)
                for(auto &p:cur) p.first = -p.first;

            auto nn = norm(cur);
            if(seen.insert(nn).second)
                res.push_back(nn);
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<string>> shapeBlocks;
    string line;

    // READ SHAPES
    while (getline(cin,line)) {
        if(line == "") continue;

        // Region starts when we see something like "12x5:"
        bool regionLine = false;
        for(char c:line) if(c=='x') regionLine = true;
        if(regionLine && line.find(':') != string::npos &&
           isdigit(line[0])) {
            // This is a region line → break, we'll process it later.
            break;
        }

        // Otherwise it's a shape header: "0:"
        if(line.back()==':'){
            vector<string> block;
            while(getline(cin,line)){
                if(line=="" || line.back()==':') break;
                bool hasDotHash=false;
                for(char c:line) if(c=='.' || c=='#') hasDotHash=true;
                if(!hasDotHash) break;
                block.push_back(line);
            }
            shapeBlocks.push_back(block);
        }
    }

    // Convert shapeBlocks → vector of coordinate sets
    vector<vector<pair<int,int>>> shapes;
    for(auto &blk:shapeBlocks){
        vector<pair<int,int>> pts;
        for(int y=0;y<(int)blk.size();y++)
            for(int x=0;x<(int)blk[y].size();x++)
                if(blk[y][x]=='#') pts.push_back({x,y});
        shapes.push_back(norm(pts));
    }

    int S = shapes.size();
    vector<vector<vector<pair<int,int>>>> variants(S);
    for(int i=0;i<S;i++)
        variants[i] = genAllVariants(shapes[i]);

    // The line we previously read is the first region
    vector<string> regionLines;
    regionLines.push_back(line);

    // Read remaining region lines
    while (getline(cin,line)) {
        if(line!="") regionLines.push_back(line);
    }

    auto idx = [&](int x,int y,int W){ return y*W + x; };

    int answer = 0;

    for(string ln : regionLines){
        if(ln=="") continue;

        // Parse "WxH: a b c d ..."
        int W,H;
        {
            auto pos = ln.find(':');
            string dims = ln.substr(0,pos);
            auto x = dims.find('x');
            W = stoi(dims.substr(0,x));
            H = stoi(dims.substr(x+1));
        }

        vector<int> need;
        {
            auto pos = ln.find(':');
            string rest = ln.substr(pos+1);
            stringstream ss(rest);
            int v;
            while(ss>>v) need.push_back(v);
            if((int)need.size() < S) need.resize(S,0);
        }

        // Build list of piece indices
        vector<int> pieces;
        int totalCells=0;
        for(int i=0;i<S;i++){
            int area = shapes[i].size();
            totalCells += area * need[i];
            while(need[i]--) pieces.push_back(i);
        }
        if(totalCells > W*H) continue; // impossible quickly

        // Precompute placements for each shape
        int N = W*H;
        int WORDS = (N+63)/64;
        vector<vector<vector<uint64_t>>> placements(S);

        for(int si=0; si<S; si++){
            auto &vars = variants[si];
            for(auto &v: vars){
                int maxx=0,maxy=0;
                for(auto&p:v){
                    maxx=max(maxx,p.first);
                    maxy=max(maxy,p.second);
                }
                for(int dy=0; dy+maxy < H; dy++){
                    for(int dx=0; dx+maxx < W; dx++){
                        vector<uint64_t> mask(WORDS,0);
                        bool ok=true;
                        for(auto&p:v){
                            int x=dx+p.first;
                            int y=dy+p.second;
                            int id=idx(x,y,W);
                            mask[id>>6] |= (1ULL<<(id&63));
                        }
                        placements[si].push_back(mask);
                    }
                }
            }
            // dedupe masks
            sort(placements[si].begin(), placements[si].end());
            placements[si].erase(unique(placements[si].begin(), placements[si].end()), placements[si].end());
        }

        // Validate no shape impossible
        bool bad=false;
        for(int si: pieces)
            if(placements[si].empty()) bad=true;
        if(bad) continue;

        // Build instance list
        struct Inst { int shape; vector<vector<uint64_t>> *pl; };
        vector<Inst> insts;
        for(int sh : pieces)
            insts.push_back({sh, &placements[sh]});

        // Sort by fewer placements first
        sort(insts.begin(), insts.end(), [&](auto &a,auto&b){
            return a.pl->size() < b.pl->size();
        });

        vector<uint64_t> occ(WORDS,0);
        bool solved=false;

        function<void(int)> dfs = [&](int pos){
            if(solved) return;
            if(pos == (int)insts.size()){
                solved = true; return;
            }
            for(auto &m : *insts[pos].pl){
                bool ok=true;
                for(int w=0;w<WORDS;w++){
                    if(occ[w] & m[w]){ ok=false; break; }
                }
                if(!ok) continue;
                for(int w=0;w<WORDS;w++) occ[w] ^= m[w];
                dfs(pos+1);
                if(solved) return;
                for(int w=0;w<WORDS;w++) occ[w] ^= m[w];
            }
        };

        dfs(0);
        if(solved) answer++;
    }

    cout << answer << "\n";
}

// Ans: 469