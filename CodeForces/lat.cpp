#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAXN = 2e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

int p[MAXN], add[MAXN];

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void join(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return;
    p[x] = y;
    add[x] -= add[y];
 }

int get(int x) {
    return x == p[x] ? add[x] : add[x] + add[find(x)];
}

void solve(){
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        p[i] = i;
    }

    for(int i = 1; i <= m; ++i) {
        string q; cin >> q;
        if(q == "join") {
            int x, y; cin >> x >> y;
            join(x,y);
        } else if(q == "add") {
            int x, v; cin >> x >> v;
            add[find(x)] += v;
        } else {
            int x; cin >> x;
            cout << get(x) << '\n';
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int TC = 1;
    //cin >> TC;
    while(TC--){
        solve();
    }
}