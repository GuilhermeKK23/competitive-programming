#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+10;
const int MAXLOG = 20;

int pai[MAXN], anc[MAXLOG][MAXN];

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    for(int i=2; i<=n; ++i) cin >> pai[i];

    pai[1] = -1;
    for(int p=0; p<MAXLOG; ++p)
        for(int i=1; i<=n; ++i)
            anc[p][i] = -1;

    for(int i=1; i<=n; ++i) anc[0][i] = pai[i];

    for(int p=1; p<MAXLOG; ++p)
        for(int i=1; i<=n; ++i)
            if(anc[p-1][i]!=-1) anc[p][i] = anc[p-1][anc[p-1][i]];

    while(q--){
        int x, k; cin >> x >> k;
        for(int p=MAXLOG-1; p>=0; --p){
            if(x==-1) break;
            if((1<<p)<=k){
                k -= (1<<p);
                x = anc[p][x];
            }
        }

        cout << x << "\n";
    }
}