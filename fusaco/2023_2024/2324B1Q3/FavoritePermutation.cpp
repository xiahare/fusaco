#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int next_hnumber(int n1, int n2, int left, int right){
    if(n1!=left&&n1!=right){
        return n1;
    } else if(n2!=-1&&n2!=left&&n2!=right){
        return n2;
    }
    
    return -1;
}

int remain_number(vector<bool>& visited){
    for(int i=1; i<visited.size();i++){ // visited indexed from 1
        if(!visited[i]){
            return i;
        }
    }
    return -1;
}

int main() {
    int t;
    cin >> t;
    
    while(t--){
        int n;
        cin >> n;
        
        vector<bool> visited(n+1,false);
        visited[0]=true;
        int h[n]; // indexed from 1
        h[0]=-1;
        int count1=0;
        bool check_fail = false;
        
        for(int i=1;i<n;i++){
            cin >> h[i];
            if(visited[h[i]]){
                // cannot duplicate except two 1s
                if(h[i]==1){
                    count1++;
                    if(count1>1){
                        cout << -1 << endl;
                        check_fail =true;
                        break;
                    }
                }else{
                    cout << -1 << endl;
                    check_fail =true;
                    break;
                }

            } else {
                visited[h[i]]=true;
            }
        }
        if(check_fail){
            continue;
        }
        
        bool ended = false;

        deque<int> dq;
        // index 0
        dq.push_back(1);
        
        // special cases
        if(h[n-1]!=1){
            cout << -1 << endl;
            continue;
        } else {
            if(n==2){
                cout << "1 2" << endl;
                continue;
            } else if(n==3){
                if( h[1]==1 ){
                    cout << "2 1 3" << endl;
                    continue;
                } else if( h[1]==2){
                    cout << "1 2 3" << endl;
                    continue;
                } else if( h[1]==3){
                    cout << "1 3 2" << endl;
                    continue;
                }
            }
        }
                
        // when n>4 : 2 ~ (n-3)
        for(int i=2; i<=n-1; i++){
            int h_idx = n+1-i;
            int left = dq.front();
            int right = dq.back();
            if(h[h_idx] != left && h[h_idx] != right ){
                cout << -1 << endl;
                ended =true;
                break;
            }
            
            int next_v = h[h_idx-1]; // next_hnumber ( h[h_idx-1], h[h_idx-2], left, right );
            if(next_v == left || next_v == right ){
                next_v = remain_number(visited);
                visited[next_v]=true;
            }

            if(h[h_idx]==left){
                dq.push_front(next_v);
            } else {
                dq.push_back(next_v);
            }
            
        }
        
        if(!ended){
            // n-1 , n
            int h_idx = 1;
            
            if(h[h_idx] != dq.front() && h[h_idx] != dq.back() ){
                cout << -1 << endl;
                continue;
            }
            int rem = remain_number(visited);
            visited[rem]=true;
            if(h[h_idx]==dq.front()){
                dq.push_front(rem);
            } else {
                dq.push_back(rem);
            }
            visited[rem]=true;
            
            if(dq.front()<dq.back()){
                cout << dq.front();
                dq.pop_front();
                while(!dq.empty()){
                    cout << " " << dq.front();
                    dq.pop_front();
                }
            } else {
                cout << dq.back() ;
                dq.pop_back();
                while(!dq.empty()){
                    cout << " " << dq.back() ;
                    dq.pop_back();
                }
            }
            cout << endl;
        }
    }
    /**
     (n-1) (n)
     h       p
         
         1
     n-1    2
     n-2    3
     n-3    4
    n+1-i     i
     3     n-2
     2      n-1
     1     n
     */
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
