#include<bits/stdc++.h>
using namespace std;
 
int resp;
 
void bt(int i, vector<vector<char>> &a, vector<pair<int, int>> &queens){
    if(i==9){
        ++resp;
        return;
    }
 
    for(int j=1; j<=8; ++j){
        bool val=1;
        for(auto obj:queens){
            int x = obj.first, y = obj.second;
            if(x==i || y==j){ val=0; break; }
            if(abs(x-i)==abs(y-j)){ val=0; break; }
        }
        if(!val) continue;
 
        if(a[i][j]=='.'){
            queens.push_back({i, j});
            bt(i+1, a, queens);
            queens.pop_back();
        }
    }
 
}
 
int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    vector<vector<char>> a(10, vector<char>(10));
    vector<pair<int, int>> queens;
    for(int i=1; i<=8; ++i)
        for(int j=1; j<=8; ++j)
            cin >> a[i][j];
 
    bt(1, a, queens);
    cout << resp << "\n";
}