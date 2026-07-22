#include<bits/stdc++.h>
#include<union_find.cpp>
using namespace std;

#define pb push_back

struct edge{
    int u, v, w;
};

//recebe o numero de vertices n e um grafo em forma de lista de arestas
//retorna o custo da MST e uma MST em forma de de lista de arestas
//complexidade: O(ElogE + E.alpha(V, E))
pair<int, vector<edge>> kruskal(int n, vector<edge> edges){
    sort(edges.begin(), edges.end(), [&](const edge &a, const edge &b){ return a.w<b.w; });
    UF uf(n);

    int ret = 0;
    vector<edge> mst;

    for(auto [u, v, w]:edges){
        if(uf.find(u)!=uf.find(v)){
            uf.join(u, v);
            mst.pb({u, v, w});
            ret += w;
        }
    }

    return {ret, mst};
}