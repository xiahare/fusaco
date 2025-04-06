#include <iostream>
#include <vector>

using namespace std;

/**
 NOTES: Failed for most of testcases
 */
int main() {
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<bool>> v(n,vector<bool>(n,'D'));
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            char c;
            cin >> c;
            v[i][j] = c=='W'?true:false;
            v[j][i] = c=='L'?true:false;
        }
    }
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        
        // both win count
        int k=0;
        for(int i=0; i<n; i++){
            if(v[i][a] && v[i][b]){
                k++;
            }
        }
        
        // total
        // = k*(n-k)*2 + k*k
        // = ( 2*n-k )*k
        cout << (2*n-k)*k << endl;
    }
    
    return 0;
}

/**
3 3
D
WD
LWD
1 2
2 3
1 1
--------
0
0
5
 */
