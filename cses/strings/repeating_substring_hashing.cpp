#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

int uniform(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

template<int MOD> struct mini_hash {
    static int P;
    vector<ll> h, p;
    mini_hash(){}
    mini_hash(const string& s) : h(s.size()), p(s.size()){
        p[0] = 1, h[0] = s[0];
        for (int i=1; i<s.size(); i++)
            p[i] = p[i - 1] * P % MOD, h[i] = (h[i - 1] * P + s[i]) % MOD;
    }
    ll operator()(){ // retorna hash s[0..s.size()-1]
        return h[h.size()-1];
    }
    ll operator()(int l, int r) { // retorna hash s[l...r]
        ll hash = h[r] - (l ? h[l - 1] * p[r - l + 1] % MOD : 0);
        return hash < 0 ? hash + MOD : hash;
    }
};
template<int MOD> int mini_hash<MOD>::P = uniform(256, MOD - 1); // l > |sigma|

struct super_hash {
    mini_hash<(int)1e9+7> h1;
    mini_hash<(int)1e9+9> h2;

    super_hash() {}
    super_hash(const string& s) : h1(s), h2(s) {}
    ll operator()(){ return h1() + h2()*((int)(1e9+7)); }
    ll operator()(int l, int r){ return h1(l, r) + h2(l, r)*((int)1e9+7); }
};

int calc(super_hash &hash, int n, int tam){
    if(tam==0) return -1;
    unordered_map<ll, int> mp;
    for(int l=0, r=tam-1; r<n; ++l, ++r){
        int h = hash(l, r);
        if(mp.find(h)!=mp.end()) return mp[h];
        mp[h] = l;
    }
    return -1;
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s; cin >> s;
    int n = s.size();
    super_hash hash(s);
    int l = 0, r = n;
    while(l+1<r){
        int m = (l+r)/2;
        int val = calc(hash, n, m);
        if(val!=-1) l = m;
        else r = m;
    }
    
    if(l==0) cout << "-1\n";
    else cout << s.substr(calc(hash, n, l), l) << "\n";
}