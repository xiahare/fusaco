#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

struct P {
    int x, y;
};

vector<vector<P>> adjs={{{0,1}},{{1,0}},{{0,-1}},{{-1,0}},{{0,1},{1,0},{0,-1},{-1,0}}}; // 0-R, 1-D, 2-L, 3-U, 4-?
int N;
int fail_cnt = 0;
bool dfs(P curr, P last, vector<vector<bool>> & fail,vector<vector<bool>> & succ, vector<vector<bool>> & vis, vector<vector<int>> & a){
    if( curr.x<0 || curr.x>=N || curr.y <0 || curr.y>=N || succ[curr.x][curr.y] ){
        // succ or outbound
        succ[last.x][last.y] = true;
        return true;
    }
    if( !(curr.x<0 || curr.x>=N || curr.y <0 || curr.y>=N) && (fail[curr.x][curr.y]==true||vis[curr.x][curr.y]) ){
        return false;
    }
    
    vis[curr.x][curr.y] = true;
    // adjs
    for( auto adj : adjs[a[curr.x][curr.y]] ){
        P nextP = {curr.x + adj.x, curr.y + adj.y };
        bool r = dfs(nextP,curr,fail, succ,vis, a);
        if(r){
            // can go, cuur point succ
            succ[curr.x][curr.y] = true;
            return true;
        }
    }
    vis[curr.x][curr.y] = false; // backtracking
    
    return false;
}

int main() {
    int Q;
    cin >> N >> Q;
    vector<vector<bool>> fail(N,vector<bool>(N,false));
    vector<vector<int>> a(N,vector<int>(N,4)); // init ?
    
    while(Q--){
        int x,y;
        char c;
        cin >> x >> y >> c;
        x--;
        y--;
        if (c=='R'){
            a[x][y] = 0;
        } else if(c=='D'){
            a[x][y] = 1;
        } else if(c=='L'){
            a[x][y] = 2;
        } else if(c=='U'){
            a[x][y] = 3;
        }
        vector<vector<bool>> succ(N,vector<bool>(N,false));
        
        for(int i=0; i<N; i++){
            for(int j=0;j<N;j++){
                if( fail[i][j] || succ[i][j] ) continue;
                vector<vector<bool>> vis(N,vector<bool>(N,false));
                bool success = dfs({i,j},{i,j},fail, succ,vis, a);
                if(!success){
                    fail[i][j]=true;
                    fail_cnt++;
                }
                
            }
        }
        cout << fail_cnt << endl;
    }
    return 0;
}

/**
3 5
1 1 R
3 3 L
3 2 D
1 2 L
2 1 U
-------
0
0
0
2
3

3 8
1 1 R
1 2 L
1 3 D
2 3 U
3 3 L
3 2 R
3 1 U
2 1 D
-------
0
2
2
4
4
6
6
9

4 13
2 2 R
2 3 R
2 4 D
3 4 D
4 4 L
4 3 L
4 2 U
3 1 D
4 1 R
2 1 L
1 1 D
1 4 L
1 3 D
-------
0
0
0
0
0
0
0
0
11
11
11
11
13

 
 */
