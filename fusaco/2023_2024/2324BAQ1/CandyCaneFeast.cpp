#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n,m;
    cin >> n >> m;
    vector<long> cow_height(n);
    for(int i=0; i<n; i++){
        cin >> cow_height[i];
    }
    vector<long> candy_top(m);
    for(int i=0; i<m; i++){
        cin >> candy_top[i];
    }
    
    vector<long> candy_bottom(m,0);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(cow_height[j]>candy_bottom[i]){
                long delt = min(cow_height[j],candy_top[i])-candy_bottom[i];
                cow_height[j] = cow_height[j]+delt;
                candy_bottom[i] = candy_bottom[i]+delt;
                if(candy_bottom[i]==candy_top[i]){
                    break;
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        cout << cow_height[i] << endl;
    }
    return 0;
}


/**
3 2
3 2 5
6 1
-------
7
2
7
 */
