#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    vector<int> a(n), b(n) ;

    
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n;i++){
        cin >> b[i];
        
    }
    
    // init: middle index, left=(n-1)/2, right=n/2
    // layer algrithm: current_layer_loss_gain = l_new + r_new - l_r + last_layer_loss_gain
    //          l_new = ( mb[a[l]] -(same=self) - same_cnt + (same=self) ) + ( ma[b[l]] - (same=self)*layer_size )
    //          r_new = ( mb[a[r]] -(same=self) - same_cnt + (same=self) ) + ( ma[b[r]] - (same=self)*layer_size )
    //          l_r = (a[l]==b[r]) + (a[r]==b[l]) - (a[l]==b[l]) - (a[r]==b[r])
    // accumulate ma, mb
    // accumulate total_cnt_same: if( a[i]==b[i] ) total_cnt_same++;
    
    unordered_map<int,int> ma,mb;
    ll total_cnt_same = 0;
    ll loss_gain=0;
    ll last_layer_loss_gain=0;
    

    // init
    int l = (n-1)/2;
    int r = n/2;
    if( l==r ){
        ma[a[l]]++;
        mb[b[l]]++;
        if( a[l]==b[l] ) total_cnt_same++;
        l--;
        r++;
    }
    
    // accumulate
    while(l>-1){
        ma[a[l]]++;
        ma[a[r]]++;
        mb[b[l]]++;
        mb[b[r]]++;
        bool l_smae = (a[l]==b[l]);
        bool r_smae = (a[r]==b[r]);
        if( l_smae ) total_cnt_same++;
        if( r_smae ) total_cnt_same++;
        
        
        int layer_size = r - l + 1;
        ll l_new = ( mb[a[l]] - l_smae - total_cnt_same + l_smae ) + ( ma[b[l]] - (l_smae)*layer_size );
        ll r_new = ( mb[a[r]] - r_smae - total_cnt_same + r_smae ) + ( ma[b[r]] - (r_smae)*layer_size );
        ll l_r = (a[l]==b[r]) + (a[r]==b[l]) - (a[l]==b[l]) - (a[r]==b[r]);
        
        ll current_layer_loss_gain = l_new + r_new - l_r + last_layer_loss_gain;
        
        loss_gain += current_layer_loss_gain;
        last_layer_loss_gain = current_layer_loss_gain;
        
        l--;
        r++;
    }
    
    ll all_without_lossgain = ( (ll)n * (n+1) / 2 ) * total_cnt_same ;
    
    cout << all_without_lossgain + loss_gain << endl;
    return 0;
}
/**
3
1 3 2
3 2 1
-----
3

3
1 2 3
1 2 3
----
12

7
1 3 2 2 1 3 2
3 2 2 1 2 3 1
-------
60
 
7
1 3 2 2 1 2 2
3 2 2 1 2 2 1
----
68

7
1 2 3 2 1 2 2
3 2 2 1 2 2 1
------
69
 */
