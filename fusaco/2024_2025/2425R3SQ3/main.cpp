#include <iostream>
#include <algorithm>
using namespace std;

// 计算从 (a, b) 到 (c, d) 所需的最少操作次数
long long solve(long long a, long long b, long long c, long long d) {
    // 如果初始状态已经满足条件
    if (a == c && b == d) {
        return 0;
    }
    // 如果初始状态不满足条件
    if (a > c || b > d) {
        return -1;
    }

    long long operations = 0;
    while (c > a || d > b) {
        // 如果 c > d，说明最后一次操作是操作 1
        if (c > d) {
            if (d == b) {
                // 如果 d 已经等于 b，但 c 仍然大于 a，则无法继续操作
                if ((c - a) % d != 0) {
                    return -1;
                }
                operations += (c - a) / d;
                c = a;
            } else {
                operations += c / d;
                c %= d;
                if (c < a) {
                    return -1;
                }
            }
        }
        // 如果 d > c，说明最后一次操作是操作 2
        else if (d > c) {
            if (c == a) {
                // 如果 c 已经等于 a，但 d 仍然大于 b，则无法继续操作
                if ((d - b) % c != 0) {
                    return -1;
                }
                operations += (d - b) / c;
                d = b;
            } else {
                operations += d / c;
                d %= c;
                if (d < b) {
                    return -1;
                }
            }
        }
        // 如果 c == d，但 c != a 或 d != b，则无法继续操作
        else {
            return -1;
        }
    }
    // 检查最终状态是否等于初始状态
    if (c == a && d == b) {
        return operations;
    } else {
        return -1;
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << solve(a, b, c, d) << endl;
    }
    return 0;
}
