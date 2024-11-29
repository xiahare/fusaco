#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    int N, M; cin >> N >> M;
    string S; cin >> S;
    vector<ll> a(N);
    for (ll& i : a) cin >> i;
    vector<ll> cap = a;

    for (int t = 0; t < M; t++){
        vector<ll> new_a = a;
        for (int i = 0; i < N; i++){
            if (a[i] >= 1){
                new_a[i]--;
                if (S[i] == 'L'){
                    new_a[(i - 1 + N) % N]++;
                } 
                else{
                    new_a[(i + 1) % N]++;
                }
            }
        }
        for (int i = 0; i < N; i++){
            new_a[i] = min(new_a[i], cap[i]);
        }
        a = new_a;
    }
    
    cout << accumulate(a.begin(), a.end(), 0LL) << endl;
}
