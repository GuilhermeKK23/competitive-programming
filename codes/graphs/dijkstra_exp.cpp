#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1e5+10;
const int INF = 1e18;

int dist[2][MAXN];
vector<tuple<int, int, int>> grafo[2][MAXN];
set<tuple<int, int, int>> s;

void dijkstra(int ini, int n){
    for(int i=1; i<=n; ++i) dist[0][i] = dist[1][i] = INF;
    dist[0][ini] = dist[1][ini] = 0;
    for(int i=1; i<=n; ++i){
        s.insert({dist[0][i], i, 0});
        s.insert({dist[1][i], i, 1});
    }

    while(!s.empty()){
        int cur = get<1>(*s.begin());
        int cur_est = get<2>(*s.begin());
        s.erase(s.begin());

        for(auto obj:grafo[cur_est][cur]){
            int est = get<0>(obj), viz = get<1>(obj), d = get<2>(obj);
            if(dist[cur_est][cur] + d < dist[est][viz]){
                s.erase({dist[est][viz], viz, est});
                dist[est][viz] = dist[cur_est][cur] + d;
                s.insert({dist[est][viz], viz, est});
            }
        }
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
    for(int i=1; i<=m; ++i){
        int a, b, c; cin >> a >> b >> c;
        grafo[0][a].push_back({0, b, c});
        grafo[1][a].push_back({1, b, c});
        grafo[0][a].push_back({1, b, c/2});
    }

    dijkstra(1, n);
    cout << dist[1][n] << "\n";
}