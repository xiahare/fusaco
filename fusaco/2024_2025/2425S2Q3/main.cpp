#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n) , res(n+1);
    int total_cnt_same = 0;
    
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n;i++){
        cin >> b[i];
        if( a[i]==b[i] ) total_cnt_same++;
    }
    
    vector<vector<int>> dp(n,vector<int>(n,total_cnt_same));
    
    for(int delt=1;delt<n;delt++){ // delt -> 1, ... , n
        for(int i=0;i<n-delt;i++){ // i -> 0, ... , n-delt
            int j = i+delt; // j -> 0+delt, 1+delt, delt
            // mid_total = res[i+1][j-1], delt for (a[i]==b[j]) + (a[j]==b[i]) of swapped and (a[i]==b[i]) + (a[j]==b[j]) of origin
            dp[i][j] = dp[i+1][j-1] + (a[i]==b[j]) + (a[j]==b[i]) - (a[i]==b[i]) - (a[j]==b[j]);
        }
    }
    
    
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            res[dp[i][j]]++;
        }
    }
    
    for(int x: res){
        cout << x << endl;
    }
    return 0;
}
/**
3
1 3 2
3 2 1
-----
3
3
0
0

3
1 2 3
1 2 3
----
0
3
0
3

7
1 3 2 2 1 3 2
3 2 2 1 2 3 1
-------
0
6
14
6
2
0
0
0
 */
