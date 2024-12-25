#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

struct Event{
    int l,tp,r,cut;
    bool operator< (const Event & other) const {
        return std::tie(l, tp, r, cut) < std::tie(other.l, other.tp, other.r, other.cut);
    }
};
struct CuttingItem{
    int cutting, r;
    bool operator< (const CuttingItem & other) const{
        return std::tie(cutting, r) < std::tie(other.cutting, other.r);
    }
    bool operator> (const CuttingItem & other) const{
        return std::tie(cutting, r) > std::tie(other.cutting, other.r);
    }
};


int main() {
    
    int T; cin >> T;
    while(T--){
        int n,k; cin >> n >> k;
        vector<int> trees(n);
        for(int i=0; i<n; i++){
            cin >> trees[i];
        }

        sort(trees.begin(),trees.end());
        
        vector<Event> events;
        for(int i=0; i<n; i++){
            events.push_back( {trees[i],0,0,0} );
        }
        for(int i=0; i<k; i++){
            int l, r, t;
            cin >> l >> r >> t;
            int existing = upper_bound(trees.begin(),trees.end(),r) - lower_bound(trees.begin(), trees.end(), l);
            int cut = existing - t;
            events.push_back( {l,-1,r,cut} );
        }
        
        sort( events.begin(), events.end());
        
        int ans = 0;
        priority_queue<CuttingItem,vector<CuttingItem>, greater<CuttingItem>> pq;
        for( Event event: events ){
            if(event.tp==-1){
                pq.push({ans + event.cut,event.r});
            } else {
                while( !pq.empty() && pq.top().r<event.l){
                    pq.pop();
                }
                if( pq.empty() || pq.top().cutting>ans ){
                    ans++;
                }
            }
            
        }
        cout << ans << endl;
    }

    return 0;
}

/**
3
7 1
8 4 10 1 2 6 7
2 9 3
7 2
8 4 10 1 2 6 7
2 9 3
1 10 1
7 2
8 4 10 1 2 6 7
2 9 3
1 10 4
-------
4
4
3
 */
