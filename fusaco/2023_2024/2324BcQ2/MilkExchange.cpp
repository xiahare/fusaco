#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

using ll = long long ;
struct Group {
    char rl;
    ll most,least;
};

int positiveMod(int x, int mod){
    return ((x%mod)+mod)%mod;
}
int main() {
    //ifstream cin("/Users/lei/Downloads/prob2_bronze_feb24/7.in");
    
    int n,m;
    cin >> n >>m;
    string s;
    cin >> s;
    vector<int> a(n);
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    vector<Group> gs;
    
    // check if all same, and find the first other RL
    int pos=0;
    while( pos<n && s[pos]==s[0]  ){
        pos++;
    }
    if(pos==n){
        // all the same RL
        ll sum = 0;
        for(int i=0; i<n; i++){
            sum += a[i];
        }
        cout << sum << endl;
        return 0;
    }
    
    // find the first 'R'
    while (pos<n&&s[pos]!='R') {
        pos= positiveMod(pos+1,n);
    }
    
    // construct group
    int loop = 0,i;
    while( loop<n ){
        i = positiveMod(loop + pos,n);
        if( s[i]=='R' ){
            if(s[positiveMod(i-1,n)]=='L'){
                // case : LR
                Group g = {'R',a[i],0};
                gs.push_back(g);
            } else {
                // case : RR
                gs[gs.size()-1].most += a[i];
                if(i==positiveMod(pos-1,n)){
                    // loop last one
                    gs[gs.size()-1].least = a[i];
                }
            }
        } else {
            if(s[positiveMod(i-1,n)]=='L'){
                // case : LL
                gs[gs.size()-1].most += a[i];
            } else {
                // case : RL
                gs[gs.size()-1].least = a[positiveMod(i-1,n)];
                
                Group g = {'L',a[i],a[i]};
                gs.push_back(g);
            }
        }
        loop++;
    }
    
    ll remain = 0;
    for( auto g: gs ){
        remain += max(g.most-m, g.least);
    }
    
    cout << remain << endl;
    
    return 0;
}

/**
3 1
RRL
1 1 1
-------
2

5 20
LLLLL
3 3 2 3 3
-------
14

9 5
RRRLRRLLR
5 8 4 9 3 4 9 5 4
---------
38
 */
