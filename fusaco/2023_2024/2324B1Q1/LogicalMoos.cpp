#include <iostream>
#include <map>
#include <vector>

using namespace std;

const char T='T', F='F', D='D', R='R'; // true, false, and , or

map<string, bool> mv;

bool eval(const string& str){
    
    if(mv.find(str)!=mv.end()){
        // exist
        return mv[str];
    }
    auto pos=string::npos;
    if((pos = str.find(R))!=string::npos){
        string left = str.substr(0,pos);
        string right = str.substr(pos+1);
        if(left.size()<right.size()){
            // priority short string
            if(eval(left)){
                return true;
            } else if(eval(right)) {
                return true;
            } else {
                return false;
            }
        } else {
            if(eval(right)){
                return true;
            } else if(eval(left)) {
                return true;
            } else {
                return false;
            }
        }
    } else if((pos = str.find(D))!=string::npos){
        
        string left = str.substr(0,pos);
        string right = str.substr(pos+1);
        
        if(left.size()<right.size()){
            // priority short string
            if(eval(left)==false){
                return false;
            } else if(eval(right)==false) {
                return false;
            } else {
                return true;
            }
        } else {
            if(eval(right)==false){
                return false;
            } else if(eval(left)==false) {
                return false;
            } else {
                return true;
            }
        }
    }
    
    return false;
}

void execute(const int& n, const string& str, const int& start, const int& end, const bool& assert ){
    string strT = str.substr(0,start) + T + str.substr(end+1);
    string strF = str.substr(0,start) + F + str.substr(end+1);
    
    if ( eval(strT)==assert || eval(strF)==assert ){
        cout << "Y";
    } else {
        cout << "N";
    }
}

int main() {
    
    int n , q;
    cin >> n >> q;
    
    string ori ,tmp;
    for( int i=0; i<n; i++){
        cin>>tmp;
        if(tmp=="false"){
            ori.push_back(F);
        } else if(tmp=="true") {
            ori.push_back(T);
        } else if(tmp=="and") {
            ori.push_back(D);
        } else if(tmp=="or") {
            ori.push_back(R);
        }
    }
    
    mv["T"] = true;
    mv["F"] = false;
    
    for(int i=0; i<q; i++){
        int start, end;
        string temp;
        bool assert;
        cin >> start >> end;
        cin >> temp;

        // indexed from 0
        start--;
        end--;
        if(temp=="false"){
            assert=false;
        } else if(temp=="true") {
            assert=true;
        }
        
        execute(n,ori,start,end,assert);
    }
    cout << endl;
    return 0;
}

/**
5 7
false and true or true
1 1 false
1 3 true
1 5 false
3 3 true
3 3 false
5 5 false
5 5 true
-------
NYYYNYY


13 4
false or true and false and false and true or true and false
1 5 false
3 11 true
3 11 false
13 13 true
-------
YNYY
 */
