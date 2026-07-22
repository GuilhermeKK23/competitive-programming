#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+10;
const int MAXLOG = 20;

int pai[MAXN], anc[MAXLOG][MAXN], h[MAXN];
vector<int> grafo[MAXN];

void dfs(int cur, int cur_h){
    h[cur] = cur_h;
    for(int viz:grafo[cur]) dfs(viz, cur_h + 1);
}


int lca(int u, int v){
    if(h[u]<h[v]) swap(u, v);

    for(int p=MAXLOG-1; p>=0; --p){
        if(h[u] - (1<<p) >= h[v]) u = anc[p][u];
    }

    if(u==v) return u;

    for(int p=MAXLOG-1; p>=0; --p){
        if(anc[p][u]!=-1 && anc[p][u]!=anc[p][v]){
            u = anc[p][u];
            v = anc[p][v];
        }
    }

    return pai[u];
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q; cin >> n >> q;
    pai[1] = -1;
    for(int i=2; i<=n; ++i){
        cin >> pai[i];
        grafo[pai[i]].push_back(i);
    }

    dfs(1, 0);

    for(int p=0; p<MAXLOG; ++p)
        for(int i=1; i<=n; ++i)
            anc[p][i] = -1;

    for(int i=1; i<=n; ++i) anc[0][i] = pai[i];

    for(int p=1; p<MAXLOG; ++p)
        for(int i=1; i<=n; ++i)
            if(anc[p-1][i]!=-1) anc[p][i] = anc[p-1][anc[p-1][i]];

    while(q--){
        int a, b; cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
}