#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main() {
    int N, F;
    cin >> N >> F;
    string s;
    cin >> s;
    
    set<string> sset;
    
    if(F==1){
        for(int i=0; i<N-2; i++){
            if(s[i]!=s[i+1] && s[i]!=s[i+2] && s[i+1]!=s[i+2]){
                // 1. 1!=2,2!=3,1!=3 --> 122 or 133
                sset.insert(string(1, s[i]) + s[i+1] + s[i+1]);
                sset.insert(string(1, s[i]) + s[i+2] + s[i+2]);
            } else if( s[i+1]==s[i+2] ) {
                // 2. 2==3 --> x22 except 222
                for( char x='a'; x<='z'; x++){
                    if(x!=s[i]){
                        sset.insert(string(1, x) + s[i] + s[i]);
                    }
                }
            } else if(s[i]==s[i+1] && s[i+1]!=s[i+2]){
                // 3. 1==2, 1!=3 --> 133
                sset.insert(string(1, s[i]) + s[i+2] + s[i+2]);
            } else if(s[i]==s[i+2] && s[i+1]!=s[i+2]){
                // 4. 1==3, 1!=2 --> 122
                sset.insert(string(1, s[i]) + s[i+1] + s[i+1]);
            }
        }
        
    } else {
        // F>1
        unordered_map<string,vector<int>> smap; // < axx , idx1 -> idx2 -> idx3 ... >
        
        // put into smap
        for(int i=0; i<N-2; i++){
            if( s[i]!=s[i+1] && s[i+1]==s[i+2]){
                // axx --> smap
                smap[string(1, s[i]) + s[i+1] + s[i+1]].push_back(i);
            }
        }
        
        // loop smap to check count>=F and count==F-1
        for( auto m : smap){
            auto vec = m.second;
            auto key = m.first;
            
            if( vec.size()>=F ){
                // 1. count>=F
                sset.insert(key);
            } else if ( vec.size()==F-1){
                // 2. count==F-1 , loop 3-char substring, check only one char different from substring
                for(int i=0; i<N-2; i++){
                    // need abs(j-i)>=3 for each in vec
                    bool dist_good = true;
                    for( auto j: vec){
                        if( abs(j-i)<3 ){
                            dist_good = false;
                            break;
                        }
                    }
                    if( !dist_good ){
                        continue;
                    }
                    
                    // check key[0] key[1] key[2] and s[i] s[i+1] s[i+2]
                    // exactly only one different --> sset
                    if((key[0]!=s[i] && key[1]==s[i+1] && key[2]==s[i+2])
                       ||(key[0]==s[i] && key[1]!=s[i+1] && key[2]==s[i+2])
                       ||(key[0]==s[i] && key[1]==s[i+1] && key[2]!=s[i+2])){
                        sset.insert(key);
                    }
                    
                }
                
            }
        }
        
    }
    
    cout << sset.size() << endl;
    for( auto x : sset){
        cout << x << endl;
    }
    
    return 0;
}

/**
10 2
zzmoozzmoo
-----------
1
moo


17 2
momoobaaaaaqqqcqq
----------
3
aqq
baa
cqq

3 1
ooo
-----------
25
aoo
boo
coo
doo
eoo
foo
goo
hoo
ioo
joo
koo
loo
moo
noo
poo
qoo
roo
soo
too
uoo
voo
woo
xoo
yoo
zoo
 
 
6 2
bacbaa
--------
1
baa
 */
