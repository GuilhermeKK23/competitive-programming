#include<bits/stdc++.h>
using namespace std;
 
#define ll int
const int MAXN = 1e5+10;
const int MAXAO = 7e5+10;
const int MAX = 1e5+10, UPD = 1e5+10, LOG = 18;
const int MAXS = 3*MAX+3*UPD*LOG;

struct eertree {
	int n, last, sz;
    int t[MAXAO][28];
    int s[MAXAO], len[MAXAO], suf[MAXAO];

	eertree(int N) {
		s[0] = -1;
		suf[0] = 1, len[0] = 0, suf[1] = 1, len[1] = -1;
		sz = 2, last = 0, n = 1;
	}

	void add(char c) {
		s[n++] = c -= 'a';
		while (s[n-len[last]-2] != c) last = suf[last];
		if (!t[last][c]) {
			int prev = suf[last];
			while (s[n-len[prev]-2] != c) prev = suf[prev];
			suf[sz] = t[prev][c];
			len[sz] = len[last]+2;
			t[last][c] = sz++;
		}
		last = t[last][c];
	}
};
 
namespace perseg {
	ll seg[MAXS];
	int rt[UPD], L[MAXS], R[MAXS], cnt, t;
	int n, *v;
 
	ll build(int p, int l, int r) {
		if (l == r) return seg[p] = v[l];
		L[p] = cnt++, R[p] = cnt++;
		int m = (l+r)/2;
		return seg[p] = build(L[p], l, m) + build(R[p], m+1, r);
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		rt[0] = cnt++;
		build(0, 0, n-1);
	}
	ll query(int a, int b, int p, int l, int r) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		int m = (l+r)/2;
		return query(a, b, L[p], l, m) + query(a, b, R[p], m+1, r);
	}
	ll query(int a, int b, int tt) {
		return query(a, b, rt[tt], 0, n-1);
	}
	ll update(int a, int x, int lp, int p, int l, int r) {
		if (l == r) return seg[p] = seg[lp]+x;
		int m = (l+r)/2;
		if (a <= m)
			return seg[p] = update(a, x, L[lp], L[p]=cnt++, l, m) + seg[R[p]=R[lp]];
		return seg[p] = seg[L[p]=L[lp]] + update(a, x, R[lp], R[p]=cnt++, m+1, r);
	}
	int update(int a, int x, int tt=t) {
		int old = rt[tt];
		rt[++t] = cnt++;
		update(a, x, old, rt[t], 0, n-1);
		return t;
	}
	int cur_update(int a, int x, int tt=t){
		int new_root = cnt++;
		update(a, x, rt[tt], new_root, 0, n-1);
		rt[tt] = new_root;
		return tt;
	}
};

eertree et(5e5 + 2e5+10);

bool existe[MAXN];
int raiz[MAXN], tempo[MAXAO];
vector<int> prox[MAXN];

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
 
	for(int i=0; i<MAXAO; ++i) tempo[i] = -1;

	vector<int> zero(n, 0);
	perseg::build(n, zero.data());

    for(int i=0; i<n; ++i){
        string s; cin >> s;
        int qtd = 0;
        for(int j=0; j<s.size(); ++j){
            char c = s[j];
            et.add(c);
			if(tempo[et.last]==-1){
				++qtd;
			}
			if(tempo[et.last]!=i){
				if(tempo[et.last]!=-1) prox[tempo[et.last]].push_back(i);
				tempo[et.last] = i;
			}
        }

		if(!existe[0]) existe[0] = 1, raiz[0] = perseg::update(i, qtd);
		else raiz[0] = perseg::cur_update(i, qtd);
 
        et.add('z'+1); et.add('z'+2);
    }

	int r = raiz[0];
	for(int i=0; i<n-1; ++i){
		for(int nxt:prox[i]){
			if(nxt!=-1){
				if(!existe[i+1]) existe[i+1] = 1, r = perseg::update(nxt, 1);
				else r = perseg::cur_update(nxt, 1);
			}
		}
		raiz[i+1] = r;
	}
 
    while(m--){
        int l, r; cin >> l >> r;
        --l, --r;
        cout << perseg::query(l, r, raiz[l]) << endl;
    }
}