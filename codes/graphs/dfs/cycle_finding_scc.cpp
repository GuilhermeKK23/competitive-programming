#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int INF = 1e9+10;

void dfs(int cur, int &t, vector<vector<int>> &grafo, vector<int> &pre,
vector<int> &comp, stack<int> &l, stack<int> &f){
    pre[cur] = t++;
    l.push(cur);
    for(int viz:grafo[cur]){
        if(!pre[viz]){ //forward edge
            dfs(viz, t, grafo, pre, comp, l, f);
        }else{ //back edge ou cross edge
            while(pre[viz]<pre[l.top()]){
                f.push(l.top());
                l.pop();
            }
        }
    }

    if(cur==l.top()){
        while(f.size() && pre[cur]<pre[f.top()]){
            int x = f.top(); f.pop();
            comp[x] = cur, pre[x] = INF;
        }
        l.pop();
        comp[cur] = cur, pre[cur] = INF;
    }
}

//recebe o numero de vertices n e um grafo em forma de lista de adjacencia
//0-indexado
//retorna um vector em que comp[i] eh o lider da componente do vertice i
vector<int> cycle_finding(int n, vector<vector<int>> &grafo){
    int t = 1;
    vector<int> pre(n), comp(n);
    stack<int> l, f;
    for(int i=0; i<n; ++i) if(!pre[i]) dfs(i, t, grafo, pre, comp, l, f);
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

    vector<int> comp = cycle_finding(n+1, grafo), resp(n+10);
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