#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
const int INF = 1e18+10;

//recebe o numero de vertices n, um vertice de inicio ini, e um grafo com os vizinhos e os pesos
//supoe que os pesos sao nao negativos
//retorna um vetor de distancias a partir do vertice de inicio ini
//complexidade: O(V^2+E)
vector<int> dijkstra(int n, int ini, vector<vector<pii>> &grafo){
    vector<int> dist(n, INF), marc(n);
    dist[ini] = 0;
    while(true){
        int v = -1, d = INF;
        for(int i=0; i<n; ++i){
            if(!marc[i] && dist[i]<d) v = i, d = dist[i];
        }
        if(v==-1) break;
        marc[v] = 1;
        for(auto [viz, c]:grafo[v]){
            if(dist[v]+c<dist[viz]){
                dist[viz] = dist[v]+c;
            }
        }
    }
    return dist;
}