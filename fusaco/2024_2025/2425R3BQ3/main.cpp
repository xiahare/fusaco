#include <iostream>
#include <vector>
#include <map>
#include <climits>

using namespace std;

struct closeRange {
    int start = -1, end = -1;

    // Constructor to initialize start and end
    closeRange(int s = -1, int e = -1) : start(s), end(e) {}
};

bool checkK1(const vector<int>& v, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        if (v[i] != v[i - 1]) {
            return false;
        }
    }
    return true;
}

bool checkSimpleK2(const vector<int>& v, int start, int end) {
    int cnt = 0;
    for (int i = start + 1; i <= end; i++) {
        if (v[i] != v[i - 1]) {
            if (cnt > 0) {
                return false;
            }
            cnt++;
        }
    }
    return true;
}

closeRange periodSubarr(const vector<int>& v, int start, int end) {
    int a = start, b = end;
    int size = end - start + 1;
    if (size <= 2) return {a, b}; // Use constructor

    for (int sub_len = 2; sub_len < size; sub_len++) { // Fixed loop condition
        if (size % sub_len != 0) continue;
        int sub_cnt = size / sub_len;
        int s0 = start, e0 = start + sub_len - 1;
        bool valid = true;
        for (int i = 0; i < sub_len; i++) {
            for (int j = 1; j < sub_cnt; ++j) {
                if (v[s0 + j * sub_len + i] != v[s0 + i]) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
        if (valid) {
            a = s0;
            b = e0;
            break;
        }
    }
    return {a, b}; // Use constructor
}

bool checkK2(const vector<int>& v, int start, int end) {
    auto sub_range = periodSubarr(v, start, end);
    return checkSimpleK2(v, sub_range.start, sub_range.end);
}

bool checkK3(const vector<int>& v, int start, int end) {
    auto sub_range = periodSubarr(v, start, end);
    if (sub_range.end - sub_range.start > 2) {
        for (int i = sub_range.start + 1; i <= sub_range.end - 1; i++) {
            closeRange left_range{sub_range.start, i}; // Use constructor
            closeRange right_range{i + 1, sub_range.end}; // Use constructor
            // left k=1, right k=2
            if (checkK1(v, left_range.start, left_range.end) && checkK2(v, right_range.start, right_range.end)) {
                return true;
            }
            // left k=2, right k=1
            if (checkK2(v, left_range.start, left_range.end) && checkK1(v, right_range.start, right_range.end)) {
                return true;
            }
        }
        return false;
    }
    return true;
}

int main() {

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        string ans = "YES";

        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        if (ans == "YES") {
            if (k == 1) {
                if (!checkK1(a, 0, n - 1)) {
                    ans = "NO";
                }
            } else if (k == 2) {
                if (!checkK2(a, 0, n - 1)) {
                    ans = "NO";
                }
            } else if (k == 3) {
                if (!checkK3(a, 0, n - 1)) {
                    ans = "NO";
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}



/**
2
1 1
1
4 1
1 1 1 1
------------
YES
YES
 
 
 
11
4 2
1 2 2 2
4 2
1 1 2 1
4 2
1 1 2 2
6 2
1 1 2 2 1 1
10 2
1 1 1 2 2 1 1 1 2 2
8 3
3 3 1 2 2 1 2 2
9 3
1 1 2 2 2 3 3 3 3
16 3
2 2 3 2 2 3 1 1 2 2 3 2 2 3 1 1
24 3
1 1 2 2 3 3 3 2 2 3 3 3 1 1 2 2 3 3 3 2 2 3 3 3
9 3
1 2 2 1 3 3 1 2 2
6 3
1 2 1 2 2 3
------
YES
NO
YES
NO
YES
YES
YES
YES
YES
NO
NO
 */
