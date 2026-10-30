#include<bits/stdc++.h>
using namespace std;

struct vertex{
    int v;
    int cost;
    int successor;
};

struct path{

};

//struct path{
    void makepath(vertex v){}
    int findpath(vertex v){}
    int findtail(path p){}
    int findcost(path p){}
    void addpathcost(path p, int x){}
    path join(path p, path v, path q){}
    void split(vertex v){}
//};

//struct linkcuttree{
    void maketree(vertex &v){
        makepath(v);
        v.successor = NULL;
    }

    int findroot(vertex v){
        return findtail(expose(v));
    }

    pair<int, int> findcost(vertex v){
        return findpathcost(expose(v));
    }

    void addcost(vertex v, int x){
        addpathcost(expose(v), x);
    }

    void link(int v, int w){}

    void cut(int v){}
//};

int main(){

}