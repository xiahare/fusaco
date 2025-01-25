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
 1
 2
-----
 2

 3
 3 4 2
 5 2 3
 6 3 5
----
 4 2 3
 5 3 4
 6 4 5

 6
 8 10 5 6 7 4
 12 11 10 4 8 2
 5 4 6 7 9 8
 10 2 4 8 5 12
 6 8 7 9 3 5
 4 12 8 5 6 10
-------
 7 5 8 9 10 6
 4 2 5 6 7 3
 8 6 9 10 11 7
 5 3 6 7 8 4
 9 7 10 11 12 8
 6 4 7 8 9 5
 */
