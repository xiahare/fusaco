#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

const int MAXN = 3001;

bitset<MAXN> A[MAXN];  // A[s] 表示能击败符号 s 的所有符号集合

int main() {
    int N, M;
    cin >> N >> M;
    
    // 读取胜负关系矩阵
    vector<vector<char>> a(N+1, vector<char>(N+1, 'D'));
    for (int i = 1; i <= N; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < i; ++j) {
            a[i][j+1] = s[j];
        }
    }
    
    // 预处理胜负关系
    vector<vector<bool>> win(N+1, vector<bool>(N+1, false));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (i == j) {
                win[i][j] = false;  // 自己不能击败自己
                continue;
            }
            char c;
            if (i > j) {
                c = a[i][j];
            } else {
                c = a[j][i];
            }
            win[i][j] = (c == 'W');  // 如果 i 击败 j，则 win[i][j] = true
        }
    }
    
    // 预处理每个符号的击败集合 A[s]
    for (int s = 1; s <= N; ++s) {
        for (int i = 1; i <= N; ++i) {
            if (win[i][s]) {
                A[s].set(i);  // 将能击败 s 的符号 i 加入集合 A[s]
            }
        }
    }
    
    // 处理每个查询
    while (M--) {
        int s1, s2;
        cin >> s1 >> s2;
        
        // 计算 A[s1] 和 A[s2] 的交集
        bitset<MAXN> intersection = A[s1] & A[s2];
        int count_x = intersection.count();  // 交集中符号的数量
        
        // 计算 Bessie 的符号组合数量
        long long ans = count_x * (2 * N - count_x);
        
        // 输出结果
        cout << ans << endl;
    }
    
    return 0;
}
