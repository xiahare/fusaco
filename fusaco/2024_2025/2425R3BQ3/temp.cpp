#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Range {
    int start = -1, end = -1;
    Range(int s = -1, int e = -1) : start(s), end(e) {}
};

bool isUniform(const vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        if (arr[i] != arr[left]) return false;
    }
    return true;
}

bool isSimplePair(const vector<int>& arr, int left, int right) {
    int changes = 0;
    for (int i = left + 1; i <= right; ++i) {
        if (arr[i] != arr[i-1]) {
            if (++changes > 1) return false;
        }
    }
    return changes <= 1;
}

Range findPeriodicRange(const vector<int>& arr, int left, int right) {
    int n = right - left + 1;
    if (n <= 2) return {left, right};

    for (int len = 2; len < n; ++len) {
        if (n % len != 0) continue;
        bool valid = true;
        for (int i = 0; i < len; ++i) {
            for (int j = 1; j < n/len; ++j) {
                if (arr[left + j*len + i] != arr[left + i]) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
        if (valid) return {left, left + len - 1};
    }
    return {left, right};
}

bool isPairPattern(const vector<int>& arr, int left, int right) {
    Range r = findPeriodicRange(arr, left, right);
    return isSimplePair(arr, r.start, r.end);
}

bool isTriplePattern(const vector<int>& arr, int left, int right) {
    Range r = findPeriodicRange(arr, left, right);
    if (r.end - r.start < 2) return true;

    for (int i = r.start; i <= r.end; ++i) {
        bool leftUniform = isUniform(arr, r.start, i);
        bool rightValid = (i+1 > r.end) ? true : isPairPattern(arr, i+1, r.end);
        if (leftUniform && rightValid) return true;

        bool leftPair = isPairPattern(arr, r.start, i);
        bool rightUniform = (i+1 > r.end) ? true : isUniform(arr, i+1, r.end);
        if (leftPair && rightUniform) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<int> arr(N);
        bool valid = true;
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
            if (arr[i] > K) valid = false;
        }

        if (!valid) {
            cout << "NO\n";
            continue;
        }

        bool ans = false;
        if (K == 1) {
            ans = isUniform(arr, 0, N-1);
        } else if (K == 2) {
            ans = isPairPattern(arr, 0, N-1);
        } else {
            ans = isTriplePattern(arr, 0, N-1);
        }

        cout << (ans ? "YES" : "NO") << '\n';
    }
}
