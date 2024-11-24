#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct gp{
    int s, e;
    int gn; // indexed from 0 to n, total size (n+1), used for prefix sum
};

int findGroupNo(map<int, vector<gp>> & m, int & k, int & v){
    if(m.find(k)==m.end()){
        return -1;
    } else {
        auto vec = m[k];
        for( auto gp: vec){
            if( (gp.s<=v && v<=gp.e) || (gp.e<=v && v<=gp.s)){
                return gp.gn;
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n, p;
    cin >> n >> p;
    
    map<int, vector<gp>> mapx;
    map<int, vector<gp>> mapy;
    vector<gp> groups(p+1);
    
    vector<int> group_prefix_sum(p+1,0); // loop prefix sum
    group_prefix_sum[0]=0;

    int firstx, firsty, lastx,lasty;
    cin >> firstx >> firsty;
    lastx = firstx;
    lasty = firsty;
    
    for(int i=1; i<p; i++){
        int px, py;
        cin >> px >> py;
        // to group map
        int cur_group_len=0;
        gp tmp_group;
        if(px==lastx){
            tmp_group = {lasty,py,i};
            mapx[px].push_back( tmp_group );
        } else {
            tmp_group = {lastx,px,i};
            mapy[py].push_back( tmp_group );
        }
        groups[i] = tmp_group;
        cur_group_len = abs(tmp_group.s-tmp_group.e);
        
        // prefix sum
        group_prefix_sum[i] = group_prefix_sum[i-1] + cur_group_len;
        
        lastx = px;
        lasty = py;
    }
    
    // last one to the first one
    int cur_group_len=0;
    gp tmp_group;
    if(lastx==firstx){
        tmp_group = {lasty,firsty,p};
        mapx[firstx].push_back( tmp_group );

    } else {
        tmp_group = {lastx,firstx,p};
        mapy[firsty].push_back( tmp_group );

    }
    groups[p] = tmp_group;
    cur_group_len = abs(tmp_group.s-tmp_group.e);
    
    group_prefix_sum[p] = group_prefix_sum[p-1] + cur_group_len;
    
    int ax, ay, bx, by;

    while(n--){
        bool aInXmap = true;
        bool bInXmap = true;
        cin >> ax >> ay >> bx >> by;
        
        int shortest;
        // which group in
        int a_gn = findGroupNo(mapx, ax, ay);
        if(a_gn==-1){
            // NOT found in X map
            
            // found in Y map
            aInXmap = false;
            a_gn = findGroupNo(mapy, ay, ax);
        }
        
        int b_gn = findGroupNo(mapx, bx, by);
        if(b_gn==-1){
            // NOT found in X map
            bInXmap = false;
            // found in Y map
            b_gn = findGroupNo(mapy, by, bx);
        }
        
        if(a_gn==b_gn){
            if(aInXmap){
                shortest = abs(ay-by);
            } else {
                shortest = abs(ax-bx);
            }
        } else if(a_gn>b_gn) {
            int aLen;
            if(aInXmap){
                aLen = abs(groups[a_gn].s - ay);
            }else{
                aLen = abs(groups[a_gn].s - ax);
            }
            int bLen;
            if(bInXmap){
                bLen = abs(groups[b_gn].e - by);
            }else{
                bLen = abs(groups[b_gn].e - bx);
            }
            shortest = aLen + bLen + group_prefix_sum[a_gn-1]-group_prefix_sum[b_gn];
        } else {
            int aLen;
            if(aInXmap){
                aLen = abs(groups[a_gn].e - ay);
            }else{
                aLen = abs(groups[a_gn].e - ax);
            }
            int bLen;
            if(bInXmap){
                bLen = abs(groups[b_gn].s - by);
            }else{
                bLen = abs(groups[b_gn].s - bx);
            }
            shortest = aLen + bLen + group_prefix_sum[b_gn-1]-group_prefix_sum[a_gn];
        }
        
        if( shortest > group_prefix_sum[p]/2){
            shortest = group_prefix_sum[p] - shortest;
        }
        
        cout << shortest << endl;
    }

    return 0;
}


/**
5 4
0 0
2 0
2 2
0 2
0 0 0 2
0 2 1 0
2 1 0 2
1 0 1 2
1 2 1 0
------
2
3
3
4
4
 */
