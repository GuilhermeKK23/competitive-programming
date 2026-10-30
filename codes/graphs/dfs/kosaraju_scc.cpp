#include<bits/stdc++.h>
using namespace std;

#define pb push_back

void dfs(int v, vector<vector<int>> &grafo, vector<bool> &marc, stack<int> &s){
    marc[v] = 1;
    for(int viz:grafo[v]) if(!marc[viz]) dfs(viz, grafo, marc, s);
    s.push(v);
}

void dfs_comp(int v, vector<vector<int>> &grafo, vector<bool> &marc, int rep, vector<int> &comp){
    marc[v] = 1;
    comp[v] = rep;
    for(int viz:grafo[v]) if(!marc[viz]) dfs_comp(viz, grafo, marc, rep, comp);
}

//recebe o numero de vertices n e um grafo 0-indexado em forma de lista de adjacencia
//retorna um vetor com o lider da componente fortemente conexa de cada vertice
//complexidade: O(V+E)
vector<int> kosaraju(int n, vector<vector<int>> &grafo){
    vector<vector<int>> grafo_inv(n);
    for(int i=0; i<n; ++i){
        for(int viz:grafo[i]){
            grafo_inv[viz].pb(i);
        }
    }

    vector<bool> marc(n), marc_inv(n);
    vector<int> comp(n);
    stack<int> s;
    for(int i=0; i<n; ++i) if(!marc[i]) dfs(i, grafo, marc, s);

    while(s.size()){
        int v = s.top(); s.pop();
        if(marc_inv[v]==0) dfs_comp(v, grafo_inv, marc_inv, v, comp);
    }

    return comp;
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> grafo(n+10);
    for(int i=0; i<m; ++i){
        int u, v; cin >> u >> v;
        grafo[u].pb(v);
    }

    vector<int> comp = kosaraju(n+1, grafo), resp(n+10);
    vector<bool> marc(n+10);
    int k = 0;
    for(int i=1; i<=n; ++i){
        if(!marc[comp[i]]) resp[comp[i]] = ++k, marc[comp[i]] = 1;
        resp[i] = resp[comp[i]];
    }

    cout << k << "\n";
    for(int i=1; i<=n; ++i) cout << resp[i] << " ";
    cout << "\n";
}