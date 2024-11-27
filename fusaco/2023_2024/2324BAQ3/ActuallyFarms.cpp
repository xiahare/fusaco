#include <iostream>
#include <vector>
using namespace std;

struct Plant {
    int h,a;
};

int execute(){
    int n;
    cin >> n;
    
    vector<int> h(n);
    for(int i=0; i<n;i++){
        cin >> h[i];
    }
    vector<int> a(n);
    for(int i=0; i<n;i++){
        cin >> a[i];
    }
    vector<Plant> plants(n);
    for(int i=0; i<n;i++){
        int tmp;
        cin >> tmp;
        // sort to array
        plants[tmp] = {h[i],a[i]};
    }
    
    // no need to handle here
    if(n==1){
        cout << 0 << endl;
        return 0;
    }
    // n>2 continue
    
    int lowest=0,highest=INT32_MAX;
    for(int i=1; i<n; i++){
        Plant p1 = plants[i-1];
        Plant p2 = plants[i];
        
        int low=0,high=INT32_MAX;
        // calculate
        if( p1.a == p2.a){
            // the same acculation
            if(p1.h>p2.h){
                continue;
            } else {
                cout << -1 << endl;
                return 0;
            }
        } else {
            if(p1.a>p2.a){
                // low or all
                int a_diff = p1.a - p2.a;
                int h_diff = p2.h - p1.h;
                if(h_diff>0){
                    low = h_diff/a_diff +1;
                }
                
            } else {
                // high or imposible
                int a_diff = p2.a - p1.a;
                int h_diff = p1.h - p2.h;
                if(h_diff>0){
                    high = h_diff/a_diff;
                    if(h_diff%a_diff==0) high--;
                }
            }
        }
        lowest = max(lowest,low);
        highest = min(highest,high);
    }
    
    if(highest>=lowest){
        cout << lowest << endl;
    } else {
        cout << -1 << endl;
    }
    
    return 0;
}

int main() {
    int T ;
    cin >> T;
    
    while(T--){
        execute();
    }
    
    return 0;
}


/**
6
1
10
1
0
2
7 3
8 10
1 0
2
3 6
10 8
0 1
2
7 3
8 9
1 0
2
7 7
8 8
0 1
2
7 3
8 8
1 0
-------
0
3
2
5
-1
-1

2
5
7 4 1 10 12
3 4 5 2 1
2 1 0 3 4
5
4 10 12 7 1
3 1 1 4 5
2 4 3 1 0
--------
4
7
 
1
3
17 14 13
3 1 5
0 1 2
-----
0
 */
