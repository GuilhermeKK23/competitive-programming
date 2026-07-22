#include<bits/stdc++.h>
using namespace std;

#define pb push_back

//recebe uma string s
//retorna o pi dela
//complexidade: O(|s|)
vector<int> kmp(string &s){
    vector<int> pi(s.size());
    for(int i=1; i<s.size(); ++i){
        int j = pi[i-1];
        while(j>0 && s[i]!=s[j]) j = pi[j-1];
        if(s[i]==s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

//recebe um padrao s e um texto t
//retorna um vetor com todas as ocorrencias de s em t
//complexidade: O(|s|+|t|)
vector<int> match(string &s, string &t){
    vector<int> pi = kmp(s), ret;
    for(int i=0, j=0; i<t.size(); ++i){
        while(j>0 && t[i]!=s[j]) j = pi[j-1];
        if(t[i]==s[j]) ++j;
        if(j==s.size()){
            ret.pb(i - s.size() + 1);
            j = pi[j-1];
        }
    }
    return ret;
}