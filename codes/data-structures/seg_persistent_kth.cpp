//problem: Kth number in [L, R]
//https://www.spoj.com/problems/MKTHNUM/

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
const int MAX = 1e9+10;

struct Perseg{
	vector<int> seg, e, d;

	Perseg(): seg(2), e(2), d(2) {}

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
			seg[novo] += val;
			return novo;
		}
		int m = (ini+fim)>>1;
		if(id<=m){ int aux = update(e[novo], ini, m, id, val); e[novo] = aux; }
		else{ int aux = update(d[novo], m+1, fim, id, val); d[novo] = aux; }
		seg[novo] = seg[e[novo]] + seg[d[novo]];
		return novo;
	}

	int query(int pos, int ini, int fim, int l, int r){
		if(r<ini || fim<l) return 0;
		if(l<=ini && fim<=r) return seg[pos];
		int m = (ini+fim)>>1;
		return query(e[pos], ini, m, l, r) + query(d[pos], m+1, fim, l, r);
	}

	int kth(int pos1, int pos2, int ini, int fim, int k){
		if(ini==fim) return ini;
		int m = (ini+fim)>>1;
		int cnt = seg[e[pos2]] - seg[e[pos1]];
		if(cnt>=k) return kth(e[pos1], e[pos2], ini, m, k);
		else return kth(d[pos1], d[pos2], m+1, fim, k-cnt);
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	int n, q; cin >> n >> q;
	vector<int> a(n+10), root(n+10);
	Perseg seg;
	root[0] = 1;
	for(int i=1; i<=n; ++i){
		cin >> a[i];
		int aux = seg.update(root[i-1], -MAX, MAX, a[i], 1);
		root[i] = aux;
	}

	while(q--){
		int i, j, k; cin >> i >> j >> k;
		cout << seg.kth(root[i-1], root[j], -MAX, MAX, k) << "\n";
	}
}