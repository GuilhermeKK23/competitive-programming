#include<bits/stdc++.h>
using namespace std;

int x[410], y[410];

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; cin >> n >> m;
    for(int i=1; i<=m; ++i){
        cin >> x[i] >> y[i];
        --x[i]; --y[i];
    }

    int resp = 0;
    for(int mask=0; mask<(1<<n); ++mask){
        bool val = 1;
        for(int i=1; i<=m; ++i){
            if((mask&(1<<x[i])) && (mask&(1<<y[i]))){
                val = 0;
                break;
            }
        }

        if(val) ++resp;
    }

    cout << resp-1 << "\n";
}