//problem: maximum subarray sum in [L, R]
//https://cses.fi/problemset/task/3226/

#include<bits/stdc++.h>
using namespace std;
 
#define int long long

struct node{
    int pref = 0, in = 0, suf = 0, tot = 0;

	node operator+(const node &outro){
		node ret;
		ret.pref = max(pref, tot + outro.pref);
		ret.in = max(suf + outro.pref, max(in, outro.in));
		ret.suf = max(outro.suf, outro.tot + suf);
		ret.tot = tot + outro.tot;
		return ret;
	}
};

struct Seg{
	int n;
	vector<int> a;
	vector<node> seg;

	Seg(int n_, vector<int> a_) : n(n_), a(a_), seg(4*n) {}

	void build(int pos, int ini, int fim){
		if(ini==fim){
			int val = max(0LL, a[ini]);
			seg[pos] = {val, val, val, a[ini]};
			return;
		}
		int m = (ini+fim)/2, e = 2*pos, d = 2*pos+1;
		build(e, ini, m);
		build(d, m+1, fim);
		seg[pos] = seg[e] + seg[d];
	}
	
	node query(int pos, int ini, int fim, int l, int r){
		node ret;
		if(r<ini || fim<l) return ret;
		if(l<=ini && fim<=r) return seg[pos];
		int m = (ini+fim)/2, e = 2*pos, d = 2*pos+1;
		return query(e, ini, m, l, r) + query(d, m+1, fim, l, r);
	}
};
 
int get_resp(node resp){
    return max(max(resp.pref, resp.suf), max(resp.in, resp.tot));
}
 
int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    int n, q; cin >> n >> q;
	vector<int> a(n+10);
    for(int i=1; i<=n; ++i) cin >> a[i];

	Seg seg(n, a);
    seg.build(1, 1, n);
 
    while(q--){
        int l, r; cin >> l >> r;
        cout << get_resp(seg.query(1, 1, n, l, r)) << "\n";
    }
}