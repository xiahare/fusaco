#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct info{
    int cnt = 0;
    int idx1=-1, idx2=-1;
    
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> vdis(n); // distinct number except self
    map<int, info> m;
    for(int i=0;i<n;i++){
        
        cin >> a[i];
        vdis[i] = (int) m.size() - (int) m.count(a[i]);
        info &x = m[a[i]];
        x.cnt++;
        x.idx1 = x.idx2;
        x.idx2 = i;
    }
    
    long long total = 0;
    for( auto &x: m ){
        auto inf = x.second ;
        if(inf.cnt>1 ){
            total += vdis[inf.idx1];
        }
    }
    cout << total << endl;
    return 0;
}


/**
6
1 2 3 4 4 4
----
3
 */
