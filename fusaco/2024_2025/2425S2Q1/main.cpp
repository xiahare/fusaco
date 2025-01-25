#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void execute(){
    int N, A, B;
    cin >> N >> A >> B;
    vector<vector<char>> a(N, vector<char>(N, 'W'));
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> a[i][j];
        }
    }
    
    int cnt = 0;
    if(A==0 && B==0){
        // A==0 && B==0 , total B and G count
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if( a[i][j]!='W' ){
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
        return ;
    }
    auto outbound = [&](int x, int y) -> bool {
        if(x<0 || y<0){
            return true;
        } else {
            return false;
        }
    };
    vector<vector<bool>> res(N, vector<bool>(N, false));
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if( a[i][j]=='B' ){
                int reverseX = i-B;
                int reverseY = j-A;
                if( outbound(reverseX, reverseY) || a[reverseX][reverseY]=='W' ){
                    cout << -1 << endl;
                    return;
                } else {
                    res[i][j] = true;
                    res[reverseX][reverseY] = true;
                }
            } else if( a[i][j]=='G' ) {
                int reverseX = i-B;
                int reverseY = j-A;
                if( outbound(reverseX, reverseY) || a[reverseX][reverseY]=='W' ){
                    res[i][j] = true;
                } else if( a[reverseX][reverseY]=='G' && res[reverseX][reverseY]==false ){
                    res[i][j] = true;
                }
            }
        }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if( res[i][j] ){
                cnt++;
            }
        }
    }
    cout << cnt << endl;
    
}

int main() {
    int T;
    cin >> T;
    while (T--){
        execute();
    }
    return 0;
}

/**
2
3 0 0
WWB
BBB
GGG
4 1 1
GWWW
WGWW
WWGW
WWWG
-----
7
2

3
5 1 2
GWGWW
WGWWW
WBWGW
WWWWW
WWGWW
3 1 1
WWW
WBW
WWW
3 1 0
GGB
GGW
WWW
----
4
-1
4
 
 */
