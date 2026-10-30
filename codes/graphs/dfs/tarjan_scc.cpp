#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int INF = 1e9+10;

void dfs(int cur, int &t, vector<vector<int>> &grafo, vector<bool> &lead, vector<int> &low, vector<int> &comp, stack<int> &s){
    lead[cur] = true;
    low[cur] = t++;
    for(int viz:grafo[cur]){
        if(!low[viz]) dfs(viz, t, grafo, lead, low, comp, s);
        if(low[viz]<low[cur]) low[cur] = low[viz], lead[cur] = false;
    }

    if(lead[cur]){
        while(s.size() && low[s.top()]>=low[cur]){
            int x = s.top(); s.pop();
            comp[x] = cur, low[x] = INF;
        }
        comp[cur] = cur, low[cur] = INF;
    }else{
        s.push(cur);
    }
}

//recebe um inteiro n e um grafo 0-indexado em forma de lista de adjacencia
//retorna um vetor em que comp[u] eh o lider da componente do vertice u
//complexidade: O(V+E)
vector<int> tarjan(int n, vector<vector<int>> &grafo){
    int t = 1;
    vector<bool> lead(n);
    vector<int> low(n), comp(n);
    stack<int> s;
    for(int i=0; i<n; ++i) if(!low[i]) dfs(i, t, grafo, lead, low, comp, s);
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

    vector<int> comp = tarjan(n+1, grafo), resp(n+10);
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