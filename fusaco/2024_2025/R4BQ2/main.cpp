#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    while(t--){
        int n;
        cin >> n;
        unordered_map<int,int> m; // key , count
        for(int i=0; i<n ; i++){
            int x;
            cin >> x;
            m[x]++;
        }
        int m_max=0,mn_max=0,mn_cnt=0;
        for(auto &[k,v]: m){
            if(v>1){
                // v >= 2
                mn_cnt++;
                mn_max = max(mn_max,k);

            }
            m_max = max(m_max,k);

        }
        int ans = m_max==mn_max ? mn_cnt*2-1 : mn_cnt*2+1;
        cout << ans << endl;
    }
    
    return 0;
}

/**
2
4
1 1 2 3
4
3 3 2 1

-------
3
1
 */
