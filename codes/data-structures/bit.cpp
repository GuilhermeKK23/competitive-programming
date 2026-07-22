//problem: point update and range sum query
//https://cses.fi/problemset/task/1648/

#include<bits/stdc++.h>
using namespace std;
 
#define int long long

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
 
int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
	vector<int> a(n+10);
    for(int i=1; i<=n; ++i) cin >> a[i];
 
	Bit bit(n);
    for(int i=1; i<=n; ++i) bit.update(i, a[i]);
 
    while(q--){
        int op; cin >> op;
        if(op==1){
            int id, val; cin >> id >> val;
            bit.update(id, -a[id]+val);
            a[id] = val;
        }else{
            int l, r; cin >> l >> r;
            cout << bit.query(l, r) << "\n";
        }
    }
}
