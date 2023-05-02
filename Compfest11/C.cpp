#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAXN = 2e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

int par[MAXN], dep[MAXN], root[MAXN], up[MAXN];
ll val[MAXN], edge[MAXN];
vector<pair<ll,ll>>adj[MAXN];

int find(int x) {
    return root[x] == x ? x : root[x] = find(root[x]);
}

void join(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return;
    root[x] = y;
    if(dep[up[x]] < dep[up[y]]) {
        up[y] = up[x];
    }
}

void dfs(int u, int p, int d) {
    par[u] = p;
    dep[u] = d;
    for(auto cur : adj[u]) {
        if(cur.first != p) {
            dfs(cur.first, u, d + 1);
            val[cur.first] = cur.second;
        }
    }
}

void solve(){
    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        root[i] = up[i] = i;
        // root buat ngehandle yang mana aja udah digabungin
        // up buat ngehandle pergerakan ketika ingin mempertemukan dua titik
    }
    for(int i = 1; i < n; ++i) {
        ll u, v, val; cin >> u >> v >> val;
        adj[u].push_back({v, val});
        adj[v].push_back({u, val});
    }
    dfs(1, 0, 0);
    while(q--) {
        int u, v; cin >> u >> v;    
        u = up[find(u)];
        v = up[find(v)];
        ll cost = 0;
        while(u != v) {
            if(dep[u] < dep[v]) swap(u,v);
            join(u, par[u]);
            cost += val[u];
            u = up[find(par[u])];
        }
        cout << cost << '\n';
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