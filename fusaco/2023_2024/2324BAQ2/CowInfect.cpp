#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    int start=0,end=n-1;
    
    while( start<n && s[start]=='1' ){
        start++;
    }
    if(start==n){
        // all are 1s
        if(n%2==1){
            // odd
            cout << 1 << endl;
        } else {
            // even
            cout << 2 << endl;
        }
        return 0;
    }
    while(s[end]=='1'){
        end--;
    }
    // all are 0s
    if(start==0&&end==n-1){
        cout << 0 << endl;
        return 0;
    }
    

    // group length
    vector<int> g_lens;
    int record=0;
    int min_len = INT32_MAX;
    for(int i=start;i<=end;i++){
        if(s[i]=='1'){
            record++;
        } else {
            if(record>0){
                g_lens.push_back(record);
                min_len = min(min_len,record);
            }
            
            record=0;
        }
    }
    int best_infect_days = INT32_MAX;
    if(min_len%2==1){
        best_infect_days = min_len/2;
    } else {
        best_infect_days = min_len/2 -1;
    }
    
    int start1_len = start;
    int end1_len = n-1 - end;
    if(start1_len>0){
        best_infect_days = min(start1_len-1,best_infect_days);
    }
    if(end1_len>0){
        best_infect_days = min(end1_len-1,best_infect_days);
    }
    
    // add start_len and end_len group to calculate infected source
    if(start1_len!=0){
        g_lens.push_back(start1_len);
    }
    if(end1_len!=0){
        g_lens.push_back(end1_len);
    }
    
    int sources = 0;
    for(auto glen: g_lens){
        int seg = best_infect_days*2+1;
        sources = sources + (glen/seg);
        if(glen%seg!=0){
            sources++;
        }
    }
    
    cout << sources << endl;
    return 0;
}


/**
 
5
11111
------
1


6
011101
-------
4
 
 */
