//problem: range increase, range set and range query
//https://cses.fi/problemset/task/1735

#include<bits/stdc++.h>
using namespace std;
 
#define int long long

struct Seg{
	int n;
	vector<int> a, seg, lz_sum, lz_set;

	Seg(int n_, vector<int> a_) : n(n_), a(a_), seg(4*n_), lz_sum(4*n_), lz_set(4*n_) {}

	void build(int pos, int ini, int fim){
		if(ini==fim){
			seg[pos] = a[ini];
			return;
		}
		int m = (ini+fim)/2, e = 2*pos, d = 2*pos+1;
		build(e, ini, m);
		build(d, m+1, fim);
		seg[pos] = seg[e] + seg[d];
	}
	
	void refresh(int pos, int ini, int fim){
		if(lz_set[pos]==0 && lz_sum[pos]==0) return;
		if(lz_set[pos]!=0){
			seg[pos] = (fim-ini+1)*lz_set[pos];
			if(ini<fim){
				int e = 2*pos, d = 2*pos+1;
				lz_set[e] = lz_set[d] = lz_set[pos];
				lz_sum[e] = lz_sum[d] = 0;
			}
			lz_set[pos] = 0;
		}
		if(lz_sum[pos]!=0){
			seg[pos] += (fim-ini+1)*lz_sum[pos];
			if(ini<fim){
				int e = 2*pos, d = 2*pos+1;
				lz_sum[e] += lz_sum[pos];
				lz_sum[d] += lz_sum[pos];
			}
			lz_sum[pos] = 0;
		}
	}
	
	void update(int pos, int ini, int fim, int val, int l, int r, int t){
		refresh(pos, ini, fim);
		if(r<ini || fim<l) return;
		if(l<=ini && fim<=r){
			if(t==1){
				lz_sum[pos] += val;
			}else{
				lz_set[pos] = val;
				lz_sum[pos] = 0;
			}
			refresh(pos, ini, fim);
			return;
		}
		int m = (ini+fim)/2, e = 2*pos, d = 2*pos+1;
		update(e, ini, m, val, l, r, t);
		update(d, m+1, fim, val, l, r, t);
		seg[pos] = seg[e] + seg[d];
	}
	
	int query(int pos, int ini, int fim, int l, int r){
		refresh(pos, ini, fim);
		if(r<ini || fim<l) return 0;
		if(l<=ini && fim<=r) return seg[pos];
		int m = (ini+fim)/2, e = 2*pos, d = 2*pos+1;
		return query(e, ini, m, l, r) + query(d, m+1, fim, l, r);
	}
};
 
int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    int n, q; cin >> n >> q;
	vector<int> a(n+10);
    for(int i=1; i<=n; ++i) cin >> a[i];

	Seg seg(n, a);
    seg.build(1, 1, n);
 
    while(q--){
        int op; cin >> op;
        if(op==1 || op==2){
            int l, r, val; cin >> l >> r >> val;
            seg.update(1, 1, n, val, l, r, op);
        }else{
            int l, r; cin >> l >> r;
            cout << seg.query(1, 1, n, l, r) << "\n";
        }
    }
}