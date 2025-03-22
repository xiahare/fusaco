#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

const int MAXN = 3001;

bitset<MAXN> A[MAXN];  // A[s] is the set of symbols that can defeat s

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<char>> a(N+1, vector<char>(N+1, 'D'));
    for (int i = 1; i <= N; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < i; ++j) {
            a[i][j+1] = s[j];
        }
    }
    
    // Preprocess win array
    vector<vector<bool>> win(N+1, vector<bool>(N+1, false));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (i == j) {
                win[i][j] = false;
                continue;
            }
            char c;
            if (i > j) {
                c = a[i][j];
            } else {
                c = a[j][i];
            }
            if (c == 'W') {
                win[i][j] = true;
            } else if (c == 'L') {
                win[i][j] = false;
            } else { // 'D'
                win[i][j] = false;
            }
        }
    }
    
    // Preprocess A[s] bitmask
    for (int s = 1; s <= N; ++s) {
        for (int i = 1; i <= N; ++i) {
            if (win[i][s]) {
                A[s].set(i);
            }
        }
    }
    
    // Process each query
    while (M--) {
        int s1, s2;
        cin >> s1 >> s2;
        bitset<MAXN> intersection = A[s1] & A[s2];
        int count_x = intersection.count();
        int ans = count_x * (2 * N - count_x);
        cout << ans << endl;
    }
    
    return 0;
}