#include <iostream>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--){
        string s;
        cin >> s;
        cout << ((s[s.size()-1]=='0')?'E':'B') << endl;
    }
    return 0;
}
/**
3
8
10
12
-----
B
E
B
 
 */
