#include<bits/stdc++.h>
using namespace std;

// Aho-corasick 
//
// query retorna o somatorio do numero de matches de
// todas as stringuinhas na stringona
//
// insert - O(|s| log(SIGMA))
// build - O(N), onde N = somatorio dos tamanhos das strings
// query - O(|s|)

const int MAX = 5e5+10;
int pattern_node[MAX];
bool visited[MAX] = {0};

namespace aho {
	map<char, int> to[MAX];
	int link[MAX], idx, term[MAX], exit[MAX], sobe[MAX];

	void insert(string& s, int i) {
        int at = 0;
        for (char c : s) {
            auto it = to[at].find(c);
			if (it == to[at].end()) at = to[at][c] = ++idx;
			else at = it->second;;
        }
        aho::term[at]++;
        aho::sobe[at]++;
        pattern_node[i] = at; // guarda o nó terminal do padrão i
	}
#warning nao esquece de chamar build() depois de inserir
	void build() {
		queue<int> q;
		q.push(0);
		link[0] = exit[0] = -1;
		while (q.size()) {
			int i = q.front(); q.pop();
			for (auto [c, j] : to[i]) {
				int l = link[i];
				while (l != -1 and !to[l].count(c)) l = link[l];
				link[j] = l == -1 ? 0 : to[l][c];
				exit[j] = term[link[j]] ? link[j] : exit[link[j]];
				if (exit[j]+1) sobe[j] += sobe[exit[j]];
				q.push(j);
			}
		}
	}

    void query(string &text) {
        int at = 0;
        for (char c : text) {
            while (at != -1 && !to[at].count(c)) at = link[at];
            at = (at == -1 ? 0 : to[at][c]);
            int tmp = at;
            while (tmp != -1) {
                if (term[tmp]) visited[tmp] = true;
                tmp = exit[tmp];
            }
        }
    }

}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string t; cin >> t;
    int k; cin >> k;

    for (int i = 0; i < k; i++) {
        string s; cin >> s;
        aho::insert(s, i);
    }

    aho::build();
    aho::query(t);
    
    for (int i = 0; i < k; i++) {
        if (visited[pattern_node[i]]) cout << "YES\n";
        else cout << "NO\n";
    }

}