#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9+7;

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s; cin >> s;
    int n = s.size();

    vector<int> dp(n+10), lst(26, -1);
    dp[0] = 1;

    for(int i=1; i<=n; ++i){
        char c = s[i-1] - 'a';
        dp[i] = 2*dp[i-1]%MOD;
        if(lst[c]!=-1) dp[i] = (dp[i] - dp[lst[c]-1] + MOD) % MOD;
        lst[c] = i;
    }

    cout << (dp[n] - 1 + MOD) % MOD << "\n";
}