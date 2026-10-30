#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9+10;

void add(int v, int d, queue<int> &q, vector<int> &cor, vector<int> &dist){
    q.push(v);
    cor[v] = 1;
    dist[v] = d;
}

//recebe o numero de vertices n, um vertice de inicio ini e um grafo em forma de lista de adjacencia
//retorna um vetor de distancias a partir do vertice de inicio ini
//complexidade: O(V+E)
vector<int> bfs(int n, int ini, vector<vector<int>> &grafo){
    queue<int> q;
    vector<int> cor(n), dist(n, INF);
    add(ini, 0, q, cor, dist);
    while(q.size()){
        int v = q.front(); q.pop();
        cor[v] = 2;
        for(int viz:grafo[v]){
            if(cor[viz]==0) add(viz, dist[v]+1, q, cor, dist);
        }
    }
    return dist;
}