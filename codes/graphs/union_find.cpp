#include<bits/stdc++.h>
using namespace std;

//union by size com path compression
struct UF{
    int n;
    vector<int> pai, tam;

    //recebe o numero de vertices n
    //inicializa o pai e o tamanho de cada componente
    UF(int n_) : n(n_), pai(n), tam(n){
        for(int i=0; i<n; ++i) pai[i] = i, tam[i] = 1;
    }

    //recebe um vertice u
    //encontra o representante da componente de u e aplica path compression
    //complexidade: O(alpha(n))
    int find(int u){
        if(u==pai[u]) return u;
        else return pai[u] = find(pai[u]);
    }

    //recebe dois vertices u, v
    //se u, v estao em componentes distintas, une as componentes usando union by size
    //complexidade: O(alpha(n))
    void join(int u, int v){
        u = find(u), v = find(v);
        if(u==v) return;

        if(tam[u]>tam[v]) swap(u, v);
        pai[u] = v;
        tam[v] += tam[u];
    }
};