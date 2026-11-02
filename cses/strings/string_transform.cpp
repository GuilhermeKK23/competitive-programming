#include<bits/stdc++.h>
using namespace std;

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s; cin >> s;
    int n = s.size();

    vector<pair<char, int>> chars;
    for(int i=0; i<n; ++i) chars.emplace_back(s[i], i);
    sort(chars.begin(), chars.end());

    vector<int> link(n);
    for(int i=0; i<n; ++i) link[chars[i].second] = i;

    int pos = 0;
    string resp;
    for(int i=0; i<n-1; ++i){
        resp += s[pos];
        pos = link[pos];
    }
    reverse(resp.begin(), resp.end());
    cout << resp << "\n";
}