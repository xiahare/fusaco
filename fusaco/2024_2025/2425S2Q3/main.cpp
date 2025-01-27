#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    
    if(n==1){
        cout << 2 << endl;
        return 0;
    }
    
    vector<vector<int>> tab(n,vector<int>(n));
    int MAX_LEN = 2*n+1;
    vector<int> freq(MAX_LEN,0);
    
    auto getOriginValue = [&](int cnt, int isLarge) -> int {
        if(isLarge==0){
            return cnt + 1;
        } else {
            return 2*n - cnt + 1;
        }
    };
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> tab[i][j];
            freq[tab[i][j]]++;
        }
    }
    vector<int> min_freq_x;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(freq[tab[i][j]]==1){
                min_freq_x.push_back(i);
            }
        }
    }
    
    //mapping opt1
    vector<int> mapping_opt1(MAX_LEN,0);
    for(int j=0;j<n;j++){
        for(int k=0; k<2; k++){
            int curr = tab[min_freq_x[k]][j];
            int origin = getOriginValue(freq[curr],k);
            mapping_opt1[curr] = origin;
        }
    }
    
    vector<vector<int>> res_opt1(n,vector<int>(n));
    vector<vector<int>> res_opt2(n,vector<int>(n));
    int sum = 2*n+2;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res_opt1[i][j] = mapping_opt1[tab[i][j]];
            res_opt2[i][j] = sum - mapping_opt1[tab[i][j]];
        }
    }
    
    vector<vector<int>> &res = res_opt1;
    for(int i=0;i<n;i++){
        if(res_opt1[i][0]>res_opt1[i][0]){
            res = res_opt2;
            break;
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << res[i][j] << " ";
        }
        cout << endl;
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
