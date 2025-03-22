#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;
using ll = long long;
int main() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    
    unordered_map<char,vector<int>> m; // key, index_vector
    for(int i=0; i<n; i++){
        char c = s[i];
        m[c].push_back(i);
    }
    
    while(q--){
        int a, b; // indexed from 1
        cin >> a >> b;
        a--;
        b--;
        
        ll max_area = -1;
        // calculate area from map
        for( auto &[key,v]: m){
            int l, r;
            l = lower_bound(v.begin(), v.end(), a)-v.begin();
            r = upper_bound(v.begin(), v.end(), b)-v.begin()-1;
            if(r-l<1){
                continue;
            }
            int moo1=a, v_idx=l;
            
            while( s[moo1]==key && v_idx<r-1 ){
                moo1++;
                v_idx++;
            }
            if( s[moo1]!=key && v_idx<r ){
                // can calculate max area
                ll i = moo1,k=v[r];
                ll v_jmax = lower_bound(v.begin(), v.end(), (i+k)/2)-v.begin();
                if(v_jmax<=r){
                    ll j = v[v_jmax];
                    ll area = (j-i)*(k-j);
                    max_area = max(max_area,area);
                }
                if(v_jmax-1>=l){
                    ll j = v[v_jmax-1];
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
