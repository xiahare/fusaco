#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> p(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> p[i];
    }

    vector<int> depth(N + 1);
    vector<vector<int>> children(N + 1);
    for (int i = 1; i <= N; ++i) {
        depth[i] = depth[p[i]] + 1;
        children[p[i]].push_back(i);
    }

    vector<bool> in_library(N + 1, true);
    for (int i = 0; i <= N; ++i) {
        if (!children[i].empty()) {
            in_library[i] = false;
        }
    }

    int M;
    cin >> M;
    vector<int> words(M);
    for (int i = 0; i < M; ++i) {
        cin >> words[i];
    }

    // 如果词库中只有一个单词，直接输出0
    if (M == 1) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> last(N + 1, -1);
    vector<int> ans(M, 0);

    for (int i = M - 1; i >= 0; --i) {
        int word = words[i];
        int max_d = -1;
        int u = word;
        while (true) {
            if (last[u] > i) {
                max_d = max(max_d, depth[u]);
            }
            if (u == 0) break;
            u = p[u];
        }
        ans[i] = max_d + 1;

        u = word;
        while (true) {
            if (last[u] < i) {
                last[u] = i;
            }
            if (u == 0) break;
            u = p[u];
        }
    }

    for (int a : ans) {
        cout << a << '\n';
    }

    return 0;
}





/**
 
5
0 1 2 3 4
5
--------
0
 
 
4
0 0 1 1
4
3
2
------------
2
1
0


4
0 0 1 1
2
3
4
-----------
1
2
0
 */
