#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 510;
const int INF = 1e18;

int dist[MAXN][MAXN];

void fw(int n){
    for(int k=1; k<=n; ++k)
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m, q; cin >> n >> m >> q;

    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            if(i==j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    for(int i=1; i<=m; ++i){
        int a, b, c; cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    fw(n);

    while(q--){
        int a, b; cin >> a >> b;
        if(dist[a][b] == INF) cout << "-1\n";
        else cout << dist[a][b] << "\n";
    }
}