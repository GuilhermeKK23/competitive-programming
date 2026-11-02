#include<bits/stdc++.h>
using namespace std;

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n; cin >> n;

    vector<int> sa(n+1), rank(n+1);
    for(int i=1; i<=n; ++i){
        cin >> sa[i];
        rank[sa[i]] = i;
    }

    auto next_rank = [&](int pos){
        if(pos>=n) return 0;
        return rank[pos + 1];
    };

    vector<char> resp(n+1);
    resp[sa[1]] = 'a';
    char cur = 'a';
    for(int i=2; i<=n; ++i) {
        if(next_rank(sa[i - 1])>next_rank(sa[i])) ++cur;
        if(cur>'z'){
            cout << "-1\n";
            return 0;
        }
        resp[sa[i]] = cur;
    }

    for(int i=1; i<=n; ++i) cout << resp[i]; cout << "\n";
}