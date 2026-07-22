#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int INF = 1e11;
 
int resp, p[30];
 
void bt(int i, int x, int y, int n){
    if(i==n){
        resp = min(resp, abs(x-y));
        return;
    }
 
    bt(i+1, x+p[i+1], y, n);
    bt(i+1, x, y+p[i+1], n);
}
 
int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    int n; cin >> n;
    for(int i=1; i<=n; ++i) cin >> p[i];
 
    resp = INF;
    bt(0, 0, 0, n);
    cout << resp << "\n";
 
}