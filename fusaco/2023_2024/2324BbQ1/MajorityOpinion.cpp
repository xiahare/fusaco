
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int test(){
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> s;
    for(int i=0;i<n;i++){
        cin >> a[i];
        if((i-1>=0&&a[i]==a[i-1])||(i-2>=0&&a[i]==a[i-2])){
            s.insert(a[i]);
        }
    }
    
    if(s.empty()){
        cout << -1 << endl;
        return 0;
    }
    
    bool first = true;
    for(int e: s){
        if(first){
            first = false;
        } else {
            cout << " ";
        }
        cout << e;
    }
    cout << endl;
    return 0;
}
int main() {
    int T;
    cin >> T;
    while(T--){
        test();
    }
    return 0;
}

/**
5
5
1 2 2 2 3
6
1 2 3 1 2 3
6
1 1 1 2 2 2
3
3 2 3
2
2 1
--------
2
-1
1 2
3
-1
 */
