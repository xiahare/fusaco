#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n,s;
    cin >> n >> s;
    s--; // indexed from 0
    vector<int> typ(n);
    vector<int> val(n);
    int targets=0;
    for(int i=0;i<n;i++){
        cin >> typ[i] >> val[i];
        if(typ[i]==1){
            targets++;
        }
    }
    
    vector<int> vis(n,false);
    vector<int> last_pow_zero(n,0);
    int pow=1, dir=1, broken=0;
    while( s>=0 && s<n && broken<targets ){
        if(typ[s]==0){
            // jump pad
            // zero value for jump pad to avoid infinite loop
            if(val[s]==0){
                if(last_pow_zero[s]==pow){
                    break;
                } else {
                    last_pow_zero[s]=pow;
                }
            }
            pow = pow + val[s];
            dir = -1 * dir;
        } else {
            // target
            if(!vis[s]&&pow>=val[s]){
                vis[s] = true;
                broken++;
            }
        }
        // move
        s = s + dir*pow;
    }
    cout << broken << endl;
    return 0;
}

/**
 
5 2
0 1
1 1
1 2
0 1
1 1
------
1

6 4
0 3
1 1
1 2
1 1
0 1
1 1
-------
3
  
 */
