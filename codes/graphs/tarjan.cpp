#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9+10;

void dfs(int cur, int &t, vector<vector<int>> &grafo, vector<bool> &marc, vector<bool> &lead, vector<int> &low, vector<int> &comp, stack<int> &s){
    marc[cur] = lead[cur] = true;
    low[cur] = t++;
    for(int viz:grafo[cur]){
        if(!marc[viz]) dfs(viz, t, grafo, marc, lead, low, comp, s);
        if(low[viz]<low[cur]) low[cur] = low[viz], lead[cur] = false;
    }
    s.push(cur);
    if(lead[cur]){
        while(s.size() && low[s.top()]>=low[cur]){
            int x = s.top(); s.pop();
            comp[x] = cur, low[x] = INF;
        }
    }
}

//recebe um inteiro n e um grafo 1-indexado em forma de lista de adjacencia
//retorna um vetor em que comp[u] eh o lider da componente do vertice u
vector<int> tarjan(int n, vector<vector<int>> &grafo){
    int t = 1;
    vector<bool> marc(n+1), lead(n+1);
    vector<int> low(n+1), comp(n+1);
    stack<int> s;
    for(int i=1; i<=n; ++i) if(!marc[i]) dfs(i, t, grafo, marc, lead, low, comp, s);
    return comp;
}