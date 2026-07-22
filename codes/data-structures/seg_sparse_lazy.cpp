//problem: Code sparse segment tree with lazy propagation
//https://www.spoj.com/problems/BGSHOOT/

#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define int long long
const int MAXN = 1e9;

struct Sparseg{
	vector<int> seg, lz, e, d;

	Sparseg() : seg(2), lz(2), e(2), d(2) {}

	int create(){
		seg.pb(0); lz.pb(0); e.pb(0); d.pb(0);
		return seg.size()-1;
	}

	void refresh(int pos, int ini, int fim){
		if(lz[pos]==0) return;

		seg[pos] += lz[pos];
		if(ini<fim){
			if(e[pos]==0){ int aux = create(); e[pos] = aux; }
			if(d[pos]==0){ int aux = create(); d[pos] = aux; }
			lz[e[pos]] += lz[pos];
			lz[d[pos]] += lz[pos];
		}

		lz[pos] = 0;
	}

	void update(int pos, int ini, int fim, int l, int r){
		refresh(pos, ini, fim);
		if(fim<l || r<ini) return;
		if(l<=ini && fim<=r){
			lz[pos]++;
			refresh(pos, ini, fim);
			return;
		}
		int m = (ini+fim)>>1;
		if(e[pos]==0){ int aux = create(); e[pos] = aux; }
		if(d[pos]==0){ int aux = create(); d[pos] = aux; }
		update(e[pos], ini, m, l, r);
		update(d[pos], m+1, fim, l, r);
		seg[pos] = max(seg[e[pos]], seg[d[pos]]);
	}

	int query(int pos, int ini, int fim, int l, int r){
		refresh(pos, ini, fim);
		if(fim<l || r<ini) return 0;
		if(l<=ini && fim<=r) return seg[pos];
		int m = (ini+fim)>>1;
		return max(query(e[pos], ini, m, l, r), query(d[pos], m+1, fim, l, r));
	}
};

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    Sparseg seg;

    int n; cin >> n;
    while(n--){
        int l, r; cin >> l >> r;
        seg.update(1, 1, MAXN, l, r);
    }

    int q; cin >> q;
    while(q--){
        int l, r; cin >> l >> r;
        cout << seg.query(1, 1, MAXN, l, r) << "\n";
    }

}