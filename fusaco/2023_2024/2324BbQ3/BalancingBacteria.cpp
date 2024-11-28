#include <iostream>
#include <vector>

using namespace std;

using ll=long long;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i=0; i<n;i++){
        cin >> a[i];
    }
    ll steps = 0;
    ll total_d=0,subtotal_d=0;
    if(a[0]!=0){
        steps++;
        ll delt = 0-a[0];
        total_d=delt;
        subtotal_d=delt;
        for(int i=1; i<n;i++){
            int sign = delt<0?-1:1;
            a[i] = a[i] + delt + i*sign;
        }
    }
    
    for(int i=1; i<n;i++){
        if(a[i]==0) continue;
        
        ll delt = 0-a[i];
        steps = steps + abs(delt);
        a[i]=0;
        for(int j=i+1; j<n; j++){
            a[j] = a[j] + delt*(j-i+1);
        }
    }
    
    cout << steps << endl;
    return 0;
}


/**
2
-1 3
------
6

5
1 3 -2 -7 5
------
26
 */
