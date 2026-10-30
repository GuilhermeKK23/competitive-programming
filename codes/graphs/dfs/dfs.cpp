#include<bits/stdc++.h>
using namespace std;

void dfs(int v, int &t, vector<vector<int>> &grafo, vector<int> &cor, vector<int> &in, vector<int> &out){
    cor[v] = 1;
    in[v] = t++;
    for(int viz:grafo[v]){
        if(cor[viz]==0) dfs(viz, t, grafo, cor, in, out);
    }
    cor[v] = 2;
    out[v] = t++;
}

//recebe o numero de vertices n e um grafo em forma de lista de adjacencia
//retorna o numero de componentes, os tempos de inicio e os tempos de fim
//complexidade: O(V+E)
tuple<int, vector<int>, vector<int>> dfs_completa(int n, vector<vector<int>> &grafo){
    vector<int> cor(n), in(n), out(n);
    int t = 0, comp = 0;
    for(int i=0; i<n; ++i){
        if(cor[i]==0){
            dfs(i, t, grafo, cor, in, out);
            ++comp;
        }
    }
    return {comp, in, out};
}