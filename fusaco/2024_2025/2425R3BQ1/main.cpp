#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, u;
    cin >> n >> u;
    
    vector<vector<bool>> v(n,vector<bool>(n,false));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            char c;
            cin >> c;
            v[i][j] = (c=='#');
        }
    }
    
    auto minOps = [&](int x, int y) -> int {
        int cnt_true = v[x][y] + v[n-1-x][y] + v[x][n-1-y] +v[n-1-x][n-1-y];
        
        return 2-abs(2-cnt_true);
    };
    
    int m = n/2;
    int total_min_ops = 0;
    // total min operations
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            total_min_ops += minOps(i,j);
        }
    }
    // print total
    cout << total_min_ops << endl;
    
    while(u--){
        int x0,y0;
        cin >> x0 >> y0; // change indexed from 0
        x0--;
        y0--;
        int org = minOps(x0, y0);
        v[x0][y0] = !v[x0][y0];
        int cur = minOps(x0, y0);
        total_min_ops += cur - org;
        cout << total_min_ops << endl;
    }
    
    return 0;
}

/**
4 5
..#.
##.#
####
..##
1 3
2 3
4 3
4 4
4 4
------
4
3
2
1
0
1
 */
