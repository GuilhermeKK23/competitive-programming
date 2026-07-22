//problem: point update and range minimum query
//https://cses.fi/problemset/task/1649/

#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9+10;

struct Seg{
	int n;
	vector<int> a, seg;

	Seg(int n_, vector<int> a_) : n(n_), seg(4*n_), a(a_) {}

	void build(int pos, int ini, int fim){
		if(ini==fim){ seg[pos] = a[ini]; return; }
		int m=(ini+fim)/2, e=2*pos, d=2*pos+1;
		build(e, ini, m); build(d, m+1, fim);
		seg[pos] = min(seg[e], seg[d]);
	}

	void update(int pos, int ini, int fim, int id, int val){
		if(id<ini || id>fim) return;
		if(ini==fim){ seg[pos] = val; return; }
		int m=(ini+fim)/2, e=2*pos, d=2*pos+1;
		update(e, ini, m, id, val); update(d, m+1, fim, id, val);
		seg[pos] = min(seg[e], seg[d]);
	}

	int query(int pos, int ini, int fim, int l, int r){
		if(fim<l || ini>r) return INF;
		if(l<=ini && fim<=r) return seg[pos];
		int m=(ini+fim)/2, e=2*pos, d=2*pos+1;
		return min(query(e, ini, m, l, r), query(d, m+1, fim, l, r));
	}

};

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
	vector<int> a(n+10);
    for(int i=1; i<=n; ++i) cin >> a[i];

	Seg seg(n, a);
    seg.build(1, 1, n);

    while(m--){
        int op; cin >> op;
        if(op==1){
            int id, val; cin >> id >> val;
            seg.update(1, 1, n, id, val);
        }else{
            int l, r; cin >> l >> r;
            cout << seg.query(1, 1, n, l, r) << "\n";
        }
    }
}