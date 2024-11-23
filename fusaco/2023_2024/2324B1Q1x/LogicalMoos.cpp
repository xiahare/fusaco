#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n, q;
    cin >> n >> q;
    vector<string> s(n);
    for(int i=0; i<n; i++){
        cin >> s[i];
    }
    vector<int> group(n,INT32_MAX);
    int group_no=0;
    for(int i=0; i<n; i++){
        
        if(s[i]=="or"){
            group_no++;
        } else {
            if(i%2==0){
                group[i]=group_no;
            }
        }
    }
    vector<int> first_false_in_group(group_no+1,INT32_MAX);
    vector<int> last_false_in_group(group_no+1,-1);
    for(int i=0; i<n; i=i+2){
        if(s[i]=="false"){
            int g = group[i];
            if(first_false_in_group[g]==INT32_MAX){
                first_false_in_group[g] = i;
            }
            last_false_in_group[g]=i;
        }
    }
    int global_first_group_true=INT32_MAX;
    int global_last_group_true=-1;
    for(int i=0; i<=group_no; i++){
            if(first_false_in_group[i]==INT32_MAX){
                if(global_first_group_true==INT32_MAX){
                    global_first_group_true = i;
                }
                global_last_group_true=i;
            }
    }
    
    for(int i=0; i<q; i++){
        int l,r; string target;
        cin >> l >> r >> target;
        l--;
        r--;
        
        int lg = group[l], rg = group[r];
        if( global_first_group_true<lg || global_last_group_true>rg){
            if( target == "true"){
                cout << "Y";
            } else {
                cout << "N";
            }
        } else {
            if( target == "true" ){
                // Y or N is possible
                if( first_false_in_group[lg]<l || last_false_in_group[rg]>r){
                    // N : exist false in group
                    cout << "N";
                } else {
                    cout << "Y";
                }
            } else {
                // Y
                cout << "Y";
            }
        }
    }
    
    cout<<endl;
    return 0;
}
