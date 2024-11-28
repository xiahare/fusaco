#include <iostream>
#include <vector>

using namespace std;

using ll=long long;

int main() {
    
    int n;
    cin >> n;
    ll a[n];
    for(int i=0; i<n;i++){
        cin >> a[i];
    }
    
    ll steps = 0;
    ll total_d=0,subtotal_d=0;

    
    if(a[0]!=0){

        steps++; // only once

        total_d = 0-a[0];
        subtotal_d = total_d<0?-1:1;
    }
    
    for(int i=1; i<n;i++){
        
        // calculate
        ll delt = 0 - total_d - subtotal_d - a[i] ;
        steps = steps + abs(delt);
        
        // for next
        subtotal_d = subtotal_d + delt;
        total_d = total_d + subtotal_d;

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
