#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

using ll = long long;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        map<ll, int> mcnt; // (ai%M,count)

        // Calculate frequencies of a[i] % M
        int a = 0;
        for (int i = 0; i < N; ++i) {
            cin >> a;
            mcnt[a % M]++;
        }

        int cptN = mcnt.size();
        int extN = 2*cptN;
        vector<ll> aMoExt(extN+1,0LL);
        vector<ll> psum(extN+1,0LL);
        vector<ll> pcnt(extN+1,0LL);

        int k=1;
        for(auto &[aMo,cnt]: mcnt ){
            aMoExt[k] = aMo;
            psum[k] = psum[k-1] + aMo*cnt;
            pcnt[k] = pcnt[k-1] + cnt;
            k++;
        }
        for(auto &[aMo,cnt]: mcnt ){
            aMoExt[k] = aMo + M;
            psum[k] = psum[k-1] + (aMo + M)*cnt;
            pcnt[k] = pcnt[k-1] + cnt;
            k++;
        }
        
        ll minOpts = LLONG_MAX;
        int left = M/2, right = (M-1)/2;
        for(int i=1; i<=extN; i++){
            int x = aMoExt[i];
            if(x-left >=0 && x+right<2*M){ // odd: ...|... , even ....|...
                int idx_left = lower_bound(aMoExt.begin()+1, aMoExt.end(), x-left) - aMoExt.begin();
                ll sum_left = psum[i-1] - psum[idx_left-1];
                ll cnt_left = pcnt[i-1] - pcnt[idx_left-1];

                int idx_right = upper_bound(aMoExt.begin()+1, aMoExt.end(), x+right) - aMoExt.begin() -1;
                ll sum_right = psum[idx_right] - psum[i] ;
                ll cnt_right = pcnt[idx_right]- pcnt[i];

                minOpts = min( minOpts, x*cnt_left - sum_left + sum_right - x*cnt_right);
            }
        }

        cout << minOpts << endl;
    }

    return 0;
}
/**
2
5 9
15 12 18 3 8
3 69
1 988244353 998244853
----
10
21
 
2
5 6
15 12 18 3 8
2 6
15 12
----
6
3
 */
