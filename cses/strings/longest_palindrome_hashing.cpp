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
    mini_hash(const string& s) : h(s.size()), p(s.size()) {
        p[0] = 1, h[0] = s[0];
        for (int i = 1; i < (int)s.size(); i++)
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

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s; cin >> s;
    string rev_s = s;
    int n = s.size();
    reverse(rev_s.begin(), rev_s.end());
    super_hash hash(s), rev_hash(rev_s);

    int tam = 1, id = 0;

    for(int c=0; c<n; ++c){
        int l = 0, r = min(c, n-1-c);
        int i = c-r, j = c+r;
        int rev_c = n-1-c, rev_j = n-1-j;
        int cur = 2*r+1;

        if(hash(i, c)==rev_hash(rev_j, rev_c) && cur>tam){ tam = cur, id = i; continue; }

        while(l+1<r){
            int m = (l+r)/2;
            int i = c-m, j = c+m;
            int rev_c = n-1-c, rev_j = n-1-j;
            if(hash(i, c)==rev_hash(rev_j, rev_c)) l = m;
            else r = m;
        }

        cur = 2*l+1, i = c-l;
        if(cur>tam) tam = cur, id = i;
    }

    for(int c1=0, c2=1; c2<n; ++c1, ++c2){
        if(s[c1]!=s[c2]) continue;

        int l = 0, r = min(c1, n-1-c2);
        int i = c1-r, j = c2+r;
        int rev_c2 = n-1-c2, rev_j = n-1-j;
        int cur = 2*r+2;

        if(hash(i, c1)==rev_hash(rev_j, rev_c2) && cur>tam){ tam = cur, id = i; continue; }

        while(l+1<r){
            int m = (l+r)/2;
            int i = c1-m, j = c2+m;
            int rev_c2 = n-1-c2, rev_j = n-1-j;
            if(hash(i, c1)==rev_hash(rev_j, rev_c2)) l = m;
            else r = m;
        }

        cur = 2*l+2, i = c1-l;
        if(cur>tam) tam = cur, id = i;
    }

    cout << s.substr(id, tam) << "\n";
}