#include <iostream>

using namespace std;

int main() {
    
    int N, Q;
    cin >> N >> Q;
    int xy[N][N],yz[N][N],xz[N][N];
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            xy[i][j]=0;
            yz[i][j]=0;
            xz[i][j]=0;
        }
    }
    
    int x,y,z;
    int conf_num = 0;
    while (Q--) {
        cin >> x >> y >> z;
        xy[x][y]++;
        if(xy[x][y]==N){
            conf_num++;
        }
        yz[y][z]++;
        if(yz[y][z]==N){
            conf_num++;
        }
        xz[x][z]++;
        if(xz[x][z]==N){
            conf_num++;
        }
        cout << conf_num << endl;
    }
    
    return 0;
}

/**
2 5
0 0 0
1 1 1
0 1 0
1 0 0
1 1 0
----------
0
0
1
2
5
 */
