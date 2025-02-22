#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    map<int,int> m; // <num, cnt>
    int a;
    for(int i=0; i<n; i++){
        cin >> a;
        m[a]++;
    }
    
    vector<int> v;  // 3, 5, 9, ...
    for(auto & [num,cnt] : m){
        v.push_back(num);
    }
    
    // blanks before i, blanks_i = i - lower_bound(i)
    for(int i=0; i<=n; i++ ){
        auto it = lower_bound(v.begin(), v.end(), i);
        int exists_before_i = distance(v.begin(), it);
        int blanks_i = i - exists_before_i;
        
        cout << max(blanks_i,m[i]) << endl;
    }
    return 0;
}


/**
4
2 2 2 0
------
1
0
3
1
2
 */
