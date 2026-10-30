#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
const int INF = 1e18+10;

//recebe o numero de vertices n, um vertice de inicio ini, e um grafo com os vizinhos e os pesos
//supoe que os pesos sao nao negativos
//retorna um vetor de distancias a partir do vertice de inicio ini
//complexidade: O((V+E)logV)
vector<int> dijkstra(int n, int ini, vector<vector<pii>> &grafo){
    set<pii> s;
    vector<int> dist(n, INF);
    dist[ini] = 0;
    for(int i=0; i<n; ++i) s.insert({dist[i], i});
    while(s.size()){
        int v = s.begin()->second;
        s.erase(s.begin());
        for(auto [viz, c]:grafo[v]){
            if(dist[v]+c<dist[viz]){
                s.erase({dist[viz], viz});
                dist[viz] = dist[v]+c;
                s.insert({dist[viz], viz});
            }
        }
    }
    return dist;
}