#include<bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> p;
    int n;
 
    dsu(int _n) : n(_n) {
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
    }
 
    int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }
 
    void unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            p[x] = y;
        }
    }
};