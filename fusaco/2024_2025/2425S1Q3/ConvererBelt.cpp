#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct P {
    int x, y;
};

vector<vector<P>> adjs={{{0,1}},{{1,0}},{{-1,0}},{{0,-1}},{{0,1},{1,0},{0,-1},{-1,0}}}; // 0-R, 1-D, 2-U, 3-L, 4-?
vector<P> dirs = {{0,1},{1,0},{-1,0},{0,-1}}; //0-R, 1-D, 2-U, 3-L
int N;
int succ_cnt = 0;
bool inside(P p){
    if(p.x>=0 && p.x<N && p.y>=0 && p.y<N){
        return true;
    }
    return false;
}
bool isGood(P p, vector<vector<int>> & a, vector<vector<bool>> & succ){
    if( !inside(p) ) {
        return false;
    }
    for(auto adj: adjs[a[p.x][p.y]]){
        P adjP = {p.x + adj.x, p.y+adj.y};
        if( !inside(adjP) || succ[adjP.x][adjP.y] ){
            return true;
        }
    }
    return false;
}
void dfs(P curr , vector<vector<int>> & a, vector<vector<bool>> & succ){
    if( !isGood(curr, a, succ) || succ[curr.x][curr.y] ){
        // succ or outbound
        return ;
    }
    
    // should be succ , but haven't marked, then marked as succ
    succ[curr.x][curr.y] = true;
    succ_cnt++;

    // update for all dirs
    for( auto dir : dirs ){
        P nextP = {curr.x + dir.x, curr.y + dir.y };
        dfs(nextP, a, succ);
    }

}

int main() {
    // freopen("sq3t6.in", "r", stdin);
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int Q;
    cin >> N >> Q;
    
    int total = N*N;
    
    vector<vector<bool>> succ(N,vector<bool>(N,false));
    vector<vector<int>> a(N,vector<int>(N,4)); // init '?'=4
    
    stack<P> st;
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
        } else if(c=='U'){
            a[x][y] = 2;
        } else if(c=='L'){
            a[x][y] = 3;
        }
        st.push({x,y});
    }
    
    stack<int> st_fail_cnt;
    
    for(int i=0; i<N; i++){
        for(int j=0;j<N;j++){
            dfs({i,j}, a, succ);
        }
    }
    st_fail_cnt.push(total-succ_cnt);
    
    
    while(st.size()>1){
        P point = st.top();
        a[point.x][point.y] = 4;
        st.pop();
        if(succ_cnt<total) {
            dfs(point, a, succ);
        }
        st_fail_cnt.push(total-succ_cnt);
    }
    
    while(!st_fail_cnt.empty()){
        cout << st_fail_cnt.top() << endl;
        st_fail_cnt.pop();
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
