#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int remain_number(vector<bool>& visited){
    for(int i=1; i<visited.size();i++){ // visited indexed from 1
        if(!visited[i]){
            return i;
        }
    }
    return -1;
}

int execute(){
    int n;
    cin >> n;
    
    vector<bool> visited(n+1,false); // visited indexed from 1
    visited[0]=true;
    
    int h[n]; // indexed from 1
    h[0]=-1;
    
    // check
    bool check_fail = false;
    for(int i=1;i<n-1;i++){ // N-2: h[1]~h[n-2] exclude last one
        cin >> h[i];
        if(visited[h[i]]){
            // cannot duplicate
            check_fail = true;

        } else {
            visited[h[i]]=true;
        }
    }
    // need to read all input to avoid other tests
    cin >> h[n-1]; // h[n-1] is unuseful
    if(h[n-1]!=1 || check_fail){
        // last one must be 1
        cout << -1 << endl;
        return 0;
    }
    
    // handle normal case
    int first = remain_number(visited);
    visited[first] = true;
    int last = remain_number(visited);
    
    vector<int> results(n,-1);
    results[0] = first;
    results[n-1] = last;
    int l=0;
    int r=n-1;
    for(int i=1; i<n-1; i++){ // exclude last one
        if(results[l]>results[r]){
            results[++l] = h[i];
        } else {
            results[--r] = h[i];
        }
    }
    
    for(int i=0; i<n ; i++){
        cout << results[i] ;
        if(i!=n-1){
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}
int main() {
    int t;
    cin >> t;
    
    while(t--){
        execute();
    }

    return 0;
}

/**
5
2
1
2
2
4
1 1 1
4
2 1 1
4
3 2 1
------
1 2
-1
-1
3 1 2 4
1 2 3 4
 
 
10
8
3 6 5 8 4 2 1
8
2 5 8 4 6 7 1
7
4 6 1 3 7 1
7
3 6 7 4 5 1
7
4 5 3 6 2 1
8
8 1 6 3 5 2 1
8
8 6 4 3 1 7 1
8
8 4 1 5 6 1 3
7
3 4 6 6 6 1
7
2 5 7 4 3 3
-----------
1 2 4 8 5 6 3 7
1 7 6 4 8 5 2 3
2 3 7 1 6 4 5
1 5 4 7 6 3 2
1 2 6 3 5 4 7
4 6 3 5 2 1 8 7
2 7 1 3 4 6 8 5
-1
-1
 -1
 */
