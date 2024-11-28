#include <iostream>
#include <fstream>

using namespace std;

using ll=long long;

int main() {
    
//    ifstream cin("/Users/lei/Downloads/prob3_bronze_jan24/12.in");
//    ofstream cout("/Users/lei/Downloads/prob3_bronze_jan24/12.x1");
    
    int n;
    cin >> n;
    
    ll steps = 0;
    ll total_d=0,subtotal_d=0;

    ll a;
    /**
    That's very intresting.
    For example,
     2
     3 4
     The result will get "5".
     It means 3 operations to {0,-2} , and then need 2 operations to {0.0}
     
    I think we can just choose L=4, which means just need only 1 time to do so.
    I wonder why it could not?
    It doesn't say it cannot spray out of the region.
     
     */
//    cin >> a;
//    if(a!=0){
//        steps++; // only once
//
//        total_d = 0-a;
//        subtotal_d = total_d<0?-1:1;
//    }
    
    for(int i=0; i<n;i++){
        cin >> a;
        // calculate
        ll delt = 0 - total_d - subtotal_d - a ;
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
 
 2
 5 10
 -----
 
 */
