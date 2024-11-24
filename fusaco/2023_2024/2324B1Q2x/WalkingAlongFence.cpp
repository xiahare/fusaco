#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Point {
    int x,y;
    bool operator<= (Point& p){
        if( (x==p.x && y<=p.y)|| (y==p.y && x<=p.x) ){
            return true;
        }
        return false;
    }
    // seg length
    int operator^ (Point& p){
        return abs(x-p.x) + abs(y-p.y);
    }
    // same pos: horizontal or vertical, such as, (1,0)~(1.2)
    string operator& (Point& p){
        if(x==p.x){
            return string("x") + to_string(x);
        } else if(y==p.y){
            return string("y")+to_string(y);
        } else {
            return "("+to_string(x)+","+to_string(y)+")->("+to_string(p.x)+","+to_string(p.y)+")";
        }
    }
};

struct Seg{
    Point s, e;
    int sn; // indexed from 0 to n, total size (n+1), used for prefix sum
};

int findGroupNo(map<string, vector<Seg>> & m, string & k, Point & v){
    if(m.find(k)==m.end()){
        return -1;
    } else {
        auto vec = m[k];
        for( auto seg: vec){
            if( (seg.s<=v && v<=seg.e) || (seg.e<=v && v<=seg.s)){
                return seg.sn;
            }
        }
    }
    return -1;
}

int findGroupNoByPoint(map<string, vector<Seg>> & m, Point & v){
    string k = "x" + to_string(v.x);
    int gn = findGroupNo(m, k, v);
    if(gn==-1){
        // NOT found in X map
        k = "y" + to_string(v.y);
        // found in Y map
        gn = findGroupNo(m, k, v);
    }
    return gn;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n, p;
    cin >> n >> p;
    
    map<string, vector<Seg>> m;
    vector<Seg> segs(p+1);
    
    vector<int> seg_prefix_sum(p+1,0); // loop prefix sum
    seg_prefix_sum[0]=0;

    Point firstp, lastp;
    
    cin >> firstp.x >> firstp.y;
    lastp = firstp;
    
    for(int i=1; i<p; i++){
        Point pt;
        cin >> pt.x >> pt.y;
        // to seg map
        segs[i] = {lastp,pt,i};
        m[lastp&pt].push_back(segs[i]);
        
        // prefix sum
        seg_prefix_sum[i] = seg_prefix_sum[i-1] + (lastp^pt);
        
        lastp = pt;
    }
    
    // last one to the first one
    segs[p] = {lastp,firstp,p};
    m[lastp&firstp].push_back(segs[p]);
    
    seg_prefix_sum[p] = seg_prefix_sum[p-1] + (lastp^firstp);
    
    vector<Point> ar(n);
    vector<Point> br(n);
    for(int i=0;i<n;i++){
        Point a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        ar[i]=a;
        br[i]=b;
    }
    
    for(int i=0;i<n;i++){
        Point& a = ar[i];
        Point& b = br[i];

        int shortest;
        // which segment in
        int a_gn = findGroupNoByPoint(m, a);
        int b_gn = findGroupNoByPoint(m, b);
        if(a_gn==b_gn){
            shortest = a^b;
        } else if(a_gn<b_gn) {
            shortest = (a^(segs[a_gn].e)) +(seg_prefix_sum[b_gn-1]-seg_prefix_sum[a_gn]) + (b^(segs[b_gn].s));
        } else {
            shortest = (b^(segs[b_gn].e)) +(seg_prefix_sum[a_gn-1]-seg_prefix_sum[b_gn]) + (a^(segs[a_gn].s));
            
        }
        
        if( shortest > seg_prefix_sum[p]/2){
            shortest = seg_prefix_sum[p] - shortest;
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
