#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int MAX = 2e6+10;
 
int a[50];
vector<int> v1(MAX), v2(MAX);
 
int32_t main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
 
	int n, x; cin >> n >> x;
	for(int i=0; i<n; ++i) cin >> a[i];
 
	int id1 = 0, id2 = 0;
	for(int mask=0; mask<(1<<(n/2)); ++mask){
		int soma = 0;
		bool usa = true;
		for(int i=0; i<n/2; ++i){
			if(mask&(1<<i)) soma += a[i];
			if(soma>x){ usa = false; break; }
		}
		if(usa) v1[id1++] = soma;
	}
 
	for(int mask=0; mask<(1<<((n+1)/2)); ++mask){
		int soma = 0;
		bool usa = true;
		for(int i=0; i<(n+1)/2; ++i){
			if(mask&(1<<i)) soma += a[i+n/2];
			if(soma>x){ usa = false; break; }
		}
		if(usa) v2[id2++] = soma;
	}
 
	sort(v2.begin(), v2.begin()+id2);
 
	int resp = 0;
	for(int i=0; i<id1; ++i){
		int val = v1[i];
		int y = x - val;
		int cnt = (int)(upper_bound(v2.begin(), v2.begin()+id2, y) - lower_bound(v2.begin(), v2.begin()+id2, y));
		//cerr << cnt << "\n";
		resp += cnt;
	}
 
	cout << resp << "\n";
}