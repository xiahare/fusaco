#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> build_max_lex_subsequence(const vector<int>& a) {
    vector<int> stack;
    for (int num : a) {
        while (!stack.empty() && stack.back() < num) {
            stack.pop_back();
        }
        stack.push_back(num);
    }
    return stack;
}

vector<int> move_and_build(vector<int> a) {
    int n = a.size();
    if (n == 0) return a;

    // 预处理后缀最大值数组
    vector<int> max_right(n);
    max_right[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        max_right[i] = max(a[i], max_right[i + 1]);
    }

    // 找到需要移动的位置
    int move_index = -1;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] < max_right[i + 1]) {
            move_index = i;
            break;
        }
    }

    // 如果没有需要移动的元素，直接返回原数组
    if (move_index == -1) return a;

    // 找到目标位置
    int target_index = move_index + 1;
    for (int i = move_index + 1; i < n; ++i) {
        if (a[i] > a[move_index]) {
            target_index = i;
        } else {
            break;
        }
    }

    // 移动元素
    vector<int> new_a = a;
    int value = new_a[move_index];
    new_a.erase(new_a.begin() + move_index);
    new_a.insert(new_a.begin() + target_index, value);

    return new_a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }

        // 构造原数组的最大字典序子序列
        vector<int> original_subseq = build_max_lex_subsequence(a);

        // 移动元素并构造新数组的最大字典序子序列
        vector<int> moved_a = move_and_build(a);
        vector<int> moved_subseq = build_max_lex_subsequence(moved_a);

        // 选择较大的子序列输出
        if (moved_subseq > original_subseq) {
            for (size_t idx = 0; idx < moved_subseq.size(); ++idx) {
                if (idx > 0) cout << " ";
                cout << moved_subseq[idx];
            }
        } else {
            for (size_t idx = 0; idx < original_subseq.size(); ++idx) {
                if (idx > 0) cout << " ";
                cout << original_subseq[idx];
            }
        }
        cout << "\n";
    }

    return 0;
}



/**
 
3
5
4 3 2 1 3
6
5 1 2 6 3 4
6
4 1 3 2 1 1

-------
4 3 3 2 1
6 5 4
4 3 2 1 1
 */
