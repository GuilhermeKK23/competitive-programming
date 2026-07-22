#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
const int INF = 1e18+10;

struct edge{
    int u, v, w;
};

//recebe o numero de vertices n, um vertice de inicio ini, e um grafo em forma de lista de arestas
//detecta ciclo negativo
//retorna um bool indicando se tem ciclo negativo e um vetor de distancias a partir do vertice de inicio ini
//complexidade: O(V.E)
pair<bool, vector<int>> bellman_ford(int n, int ini, vector<edge> &edges){
    vector<int> dist(n, INF);
    dist[ini] = 0;
    bool relaxou = 0;

    for(int i=0; i<n; ++i){
        relaxou = 0;
        for(auto [u, v, w]:edges){
            if(dist[u]!=INF && dist[u]+w<dist[v]){
                dist[v] = dist[u]+w;
                relaxou = 1;
            }
        }
    }

    if(relaxou) return {1, dist};
    else return {0, dist};
}