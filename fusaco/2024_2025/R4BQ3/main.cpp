#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
using ll = long long;
int main() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    while(q--){
        int a, b; // indexed from 1
        cin >> a >> b;
        a--;
        b--;
        
        unordered_map<char,vector<int>> m; // key, index_vector
        for(int i=a; i<=b; i++){
            char c = s[i];
            m[c].push_back(i);
        }
        ll max_area = -1;
        // calculate area from map
        for( auto &[key,v]: m){
            
            int moo1=a, v_idx=0;
            
            while( s[moo1]==key && v_idx<v.size()-2 ){
                moo1++;
                v_idx++;
            }
            if( s[moo1]!=key && v_idx<v.size()-1 ){
                // can calculate area
                for(int x=v_idx; x<v.size()-1; x++){
                    ll i=moo1,j=v[x],k=v[v.size()-1];
                    ll area = (j-i)*(k-j);
                    max_area = max(max_area,area);
                }

            }
        }
        cout << max_area << endl;
        
    }
    
    return 0;
}

/**
12 5
abcabbacabac
1 12
2 7
4 8
2 5
3 10
---
28
6
1
-1
12
 
 */
