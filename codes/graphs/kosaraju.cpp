#include<bits/stdc++.h>
using namespace std;

#define pb push_back

void dfs(int v, vector<vector<int>> &grafo, vector<int> &cor, stack<int> &s){
    cor[v] = 1;
    for(int viz:grafo[v]){
        if(cor[viz]==0) dfs(viz, grafo, cor, s);
    }
    s.push(v);
}

void dfs_comp(int v, vector<vector<int>> &grafo, vector<int> &cor, int rep, vector<int> &comp){
    cor[v] = 1;
    comp[v] = rep;
    for(int viz:grafo[v]){
        if(cor[viz]==0) dfs_comp(viz, grafo, cor, rep, comp);
    }
}

//recebe o numero de vertices n e um grafo em forma de lista de adjacencia
//comprime o grafo direcionado nas componentes fortemente conexas
//retorna um vetor com o representante da componente fortemente conexa de cada vertice
//complexidade: O(V+E)
vector<int> kosaraju(int n, vector<vector<int>> &grafo){
    vector<vector<int>> grafo_inv(n);
    for(int i=0; i<n; ++i){
        for(int viz:grafo[i]){
            grafo_inv[viz].pb(i);
        }
    }

    vector<int> cor(n), cor_inv(n), comp(n);
    stack<int> s;
    for(int i=0; i<n; ++i){
        if(cor[i]==0) dfs(i, grafo, cor, s);
    }

    while(s.size()){
        int v = s.top(); s.pop();
        if(cor_inv[v]==0) dfs_comp(v, grafo_inv, cor_inv, v, comp);
    }

    return comp;
}