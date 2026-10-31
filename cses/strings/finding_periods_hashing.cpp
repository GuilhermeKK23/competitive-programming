#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define pb push_back

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

vector<int> get_periods(const string &s){
    vector<int> ret;
    ret.reserve(s.size());
    super_hash hash(s);
    for(int tam=1; tam<=s.size(); ++tam){
        bool good = true;
        int h = hash(0, tam-1);
        for(int l=0, r=tam-1; l<s.size(); l+=tam, r+=tam){
            if(r>=s.size()){
                r = s.size()-1;
                int ini_tam = r-l+1;
                if(hash(0, ini_tam-1)!=hash(l, r)){
                    good = false;
                    break;
                }
            }else{
                if(h!=hash(l, r)){
                    good = false;
                    break;
                }
            }
        }
        if(good) ret.pb(tam);
    }
    return ret;
}
 
int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    string s; cin >> s;
    vector<int> resp = get_periods(s);
    for(int val:resp) cout << val << " "; cout << "\n";
}