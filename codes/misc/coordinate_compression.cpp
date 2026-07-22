//problem: Given an array with values up to 10^9, two types of queries:
//change the value in position K to X, and count the number of values in [A, B]
//https://cses.fi/problemset/task/1144

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back

struct Bit{
    int n;
    vector<int> bit;
    Bit(int n_) : n(n_), bit(n_+10) {}

    void update(int id, int val){
        for(; id<=n; id+=id&-id) bit[id] += val;
    }

    int pref(int id){
        int ret = 0;
        for(; id; id-=id&-id) ret += bit[id];
        return ret;
    }

    int query(int l, int r){
        return pref(r) - pref(l-1);
    }
};

struct query{
    int t, l, r;
};

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n+10), cc;
    vector<query> queries(q);
    for(int i=1; i<=n; ++i){
        cin >> a[i];
        cc.pb(a[i]);
    }

    for(int i=0; i<q; ++i){
        char c; int l, r; cin >> c >> l >> r;
        if(c=='!'){
            queries[i] = {0, l, r};
            cc.pb(r);
        }else{
            queries[i] = {1, l, r};
            cc.pb(l);
            cc.pb(r);
        }
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    auto comp = [&](int x){ return (lower_bound(cc.begin(), cc.end(), x) - cc.begin() + 1); };
    auto descomp = [&](int x){ return cc[x-1]; };

    Bit bit(cc.size()+10);
    
    for(int i=1; i<=n; ++i){
        a[i] = comp(a[i]);
        bit.update(a[i], 1);
    }

    for(auto &[t, l, r]:queries){
        if(t==1){
            l = comp(l);
            r = comp(r);
        }
    }

    for(auto &[t, l, r]:queries){
        if(t==0){
            bit.update(a[l], -1);
            a[l] = comp(r);
            bit.update(a[l], 1);
        }else{
            cout << bit.query(l, r) << "\n";
        }
    }
}