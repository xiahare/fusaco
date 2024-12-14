#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>

using namespace std;
using ll = long long;
int main() {
    vector<string> arr_wr;
    int n = 10;
    map<ll,pair<ll,ll>> mr; // low and {high, prefix_sum}
    
    for(int i=2; i<=n; i++){
        for(int j=i-1; j>=0; j--){
            int q = j;
            string s;
            while(q--)s.append("4");
            s.append("5");
            q = i-1-j;
            while(q--)s.append("0");
            arr_wr.push_back(s);
            if(arr_wr.size()>1 ){
                string last = arr_wr[arr_wr.size()-2];
                if(last[0]=='4'){
                    ll low = stoll(last);
                    ll high = stoll(s);
                    if(mr.size()==0){
                        mr[low]= {high,high-low};
                    } else {
                        mr[low] = {high, (*(mr.rbegin())).second.second + (high-low)} ; // [ low, high )
                    }
                }
            }
            
        }
    }
    
    int T;
    cin >>T ;
    while(T--){
        ll N;
        cin >> N;
        if(N<45){
            cout << 0 << endl;
            continue;
        }
        auto upper = mr.upper_bound(N);
        auto pr = *(--upper);
        ll high = pr.second.first;
        ll sum = pr.second.second;
        if(N<high){
            sum = sum - ( high-N - 1);
        }
        cout << sum << endl;
    }
    return 0;
}

/**
 
4
1
100
4567
3366
-------
0
5
183
60
 */
