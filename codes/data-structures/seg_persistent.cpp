//problem: Number of distinct values in [L, R]
//https://cses.fi/problemset/task/1734
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int MAXN = 1e6+10;

struct Perseg{
    vector<int> seg, e, d;
    Perseg() : seg(2), e(2), d(2) {};

    int create(){
        seg.pb(0); e.pb(0); d.pb(0);
        return seg.size()-1;
    }

    void copy(int pos, int novo){
        seg[novo] = seg[pos], e[novo] = e[pos], d[novo] = d[pos];
    }

    int update(int pos, int ini, int fim, int id, int val){
        if(id<ini || id>fim) return pos;
        int novo = create(); copy(pos, novo);
        if(ini==fim){
            seg[novo] = val;
            return novo;
        }
        int m = (ini+fim) >> 1;
        if(id<=m){ int aux = update(e[pos], ini, m, id, val); e[novo] = aux; }
        else{ int aux = update(d[pos], m+1, fim, id, val); d[novo] = aux; }
        seg[novo] = seg[e[novo]] + seg[d[novo]];
        return novo;
    }

    int query(int pos, int ini, int fim, int l, int r){
        if(r<ini || l>fim || pos==0) return 0;
        if(l<=ini && fim<=r) return seg[pos];
        int m = (ini+fim) >> 1;
        return query(e[pos], ini, m, l, r) + query(d[pos], m+1, fim, l, r);
    }
};

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n+10), root(n+10);
    for(int i=1; i<=n; ++i) cin >> a[i];

    vector<int> marc(MAXN), lst(MAXN), prox(MAXN);
    for(int i=n; i>=1; --i){
        prox[i] = lst[a[i]];
        lst[a[i]] = i;
    }

    Perseg seg;
    root[1] = 1;
    for(int i=1; i<=n; ++i){
        if(marc[a[i]]) continue;
        root[1] = seg.update(root[1], 1, n, i, 1);
        marc[a[i]] = 1;
    }

    for(int i=2; i<=n; ++i){
        if(prox[i-1]){
            root[i] = seg.update(root[i-1], 1, n, prox[i-1], 1);
        }else{
            root[i] = root[i-1];
        }
    }

    int q; cin >> q;
    while(q--){
        int l, r; cin >> l >> r;
        cout << seg.query(root[l], 1, n, l, r) << "\n";;
    }
}