#include<bits/stdc++.h>
using namespace std;

//suffix array caixa preta
//recebe uma string s
//retorna um vetor com o suffix array de s
//complexidade: esse aqui funciona em O(nlogn), mas da pra fazer O(n)
vector<int> suffix_array(string s) {
	s += "$";
	int n = s.size(), N = max(n, 260);
	vector<int> sa(n), ra(n);
	for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];

	for(int k = 0; k < n; k ? k *= 2 : k++) {
		vector<int> nsa(sa), nra(n), cnt(N);

		for(int i = 0; i < n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[ra[i]]++;
		for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
		for(int i = n-1; i+1; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];

		for(int i = 1, r = 0; i < n; i++) nra[sa[i]] = r += ra[sa[i]] !=
			ra[sa[i-1]] or ra[(sa[i]+k)%n] != ra[(sa[i-1]+k)%n];
		ra = nra;
		if (ra[sa[n-1]] == n-1) break;
	}
	return vector<int>(sa.begin()+1, sa.end());
}

//recebe uma string s e um vetor de suffix array sa
//retorna o vetor de lcp
//complexidade: O(|s|)
vector<int> kasai(string s, vector<int> sa) {
	int n = s.size(), h = 0;
    vector<int> rnk(n), lcp(n);
    for(int i=0; i<n; ++i) rnk[sa[i]] = i;

    for(int i=0; i<n; ++i){
        if(rnk[i]==0){
            h = 0;
            continue;
        }
        int j = sa[rnk[i]-1];
        while(i+h<n && j+h<n && s[i+h]==s[j+h]) ++h;
        lcp[rnk[i]] = h;
        if(h>0) --h;
    }
    return lcp;
}