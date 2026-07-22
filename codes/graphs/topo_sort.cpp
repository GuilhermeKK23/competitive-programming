#include<bits/stdc++.h>
using namespace std;

#define pb push_back

void dfs(int v, vector<vector<int>> &grafo, vector<int> &cor, vector<int> &ord){
    cor[v] = 1;
    for(int viz:grafo[v]){
        if(cor[viz]==0) dfs(viz, grafo, cor, ord);
    }
    ord.pb(v);
}

//recebe o numero de vertices n e um grafo em forma de lista de adjacencia
//supoe que o grafo eh um DAG
//retorna um vetor com uma ordenacao topologica do grafo
vector<int> topo_sort(int n, vector<vector<int>> &grafo){
    vector<int> ord, cor(n);
    for(int i=0; i<n; ++i){
        if(cor[i]==0) dfs(i, grafo, cor, ord);
    }
    reverse(ord.begin(), ord.end());
    return ord;
}