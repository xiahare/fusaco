#include <iostream>
#include <vector>
using namespace std;

const int tmax = 1000002;
int execute(vector<int> & stat){
    int v , s;
    cin >> v >> s;
    
    if( stat[s] >= v ){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}

int main() {
   
    cin.tie(0) -> sync_with_stdio(0);
    int n,q;
    cin >> n >> q;
    vector<int> c(n);
    vector<int> t(n);
    vector<int> stat(tmax,0);
    for (int i=0; i<n ; i++) {
        cin >> c[i];
    }
    for (int i=0; i<n ; i++) {
        cin >> t[i];
        t[i]=c[i]-t[i] -1; // change to wakeup time which cannot arrive t>=t[i]
        int tmp = t[i]<0 ? 0 : t[i];
        stat[tmp] = stat[tmp] + 1;
    }
    
    // postfix sum
    for(int i=tmax-2;i>=0;i--){
        stat[i] = stat[i+1] + stat[i];
    }

    while(q--){
        execute( stat );
    }
    return 0;
}

/**
5 5
3 5 7 9 12
4 2 3 3 8
1 5
1 6
3 3
4 2
5 1
------
YES
NO
YES
YES
NO
 */
