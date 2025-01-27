#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        long long M;
        cin >> N >> M;

        vector<long long> a(N);
        vector<long long> freq(M, 0);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
            freq[a[i] % M]++;
        }

        long long minOperations = LLONG_MAX;

        // Try every possible x % M
        for (int xModM = 0; xModM < M; ++xModM) {
            long long operations = 0;

            for (int r = 0; r < M; ++r) {
                // Calculate cost to adjust residue r to xModM
                long long cost = min((r - xModM + M) % M, (xModM - r + M) % M);
                operations += freq[r] * cost;
            }

            minOperations = min(minOperations, operations);
        }

        cout << minOperations << endl;
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
 
 */
