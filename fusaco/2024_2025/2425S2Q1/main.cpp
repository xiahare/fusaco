#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n) ;
    int total_cnt_same = 0;
    
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n;i++){
        cin >> b[i];
        if( a[i]==b[i] ) total_cnt_same++;
    }
    
    vector<vector<int>> dp(2,vector<int>(n,total_cnt_same));
    
    long long res = n * total_cnt_same;
    for(int delt=1;delt<n;delt++){ // delt -> 1, ... , n
        int mainIdx = delt % 2;
        for(int i=0;i<n-delt;i++){ // i -> 0, ... , n-delt
            int j = i+delt; // j -> 0+delt, 1+delt, delt
            // mid_total = res[i+1][j-1], delt for (a[i]==b[j]) + (a[j]==b[i]) of swapped and (a[i]==b[i]) + (a[j]==b[j]) of origin
            dp[mainIdx][i] = dp[mainIdx][i+1] + (a[i]==b[j]) + (a[j]==b[i]) - (a[i]==b[i]) - (a[j]==b[j]);
            res += dp[mainIdx][i];
        }
    }
    
    cout << res << endl;
    
    return 0;
}
/**
3
1 3 2
3 2 1
-----
3

3
1 2 3
1 2 3
----
12

7
1 3 2 2 1 3 2
3 2 2 1 2 3 1
-------
60ß
 */
