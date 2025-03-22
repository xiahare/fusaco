#include <iostream>
#include <vector>

using namespace std;

/**
 NOTES: Failed for most of testcases
 */
int main() {
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<char>> v(n,vector<char>(n,'D'));
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            cin >> v[i][j];
            v[j][i] = v[i][j];
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
            if(v[i][a]=='W' && v[i][b]=='W'){
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
