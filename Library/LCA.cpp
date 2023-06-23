#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll; 
const long long N = 2e5 + 9;
const long long mod = 1e9 + 7;
const long long inf = 1e18;
const long long LOG = 18;
 
template<typename T>
void max_self(T &a, T b){
    a = a > b ? a : b;
}
 
template<typename T>
void min_self(T &a, T b){
    a = a < b ? a : b;
}

vector<int>child[N];
vector<int>depth;
vector<vector<int>>up;

void dfs(int x){
    for(int i : child[x]){
        depth[i] = depth[x] + 1;
        up[i][0] = x;
        for(int j = 1; j < LOG; ++j){
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
        dfs(i);
    }
}

int LCA(int u, int v){
    if(depth[u] < depth[v]) {
        swap(u, v);
    }
    int k = depth[u] - depth[v];
    for(int i = 0; i < LOG; ++i){
        if(k & (1 << i)) {
            u = up[u][i];
        }
    }

    if(u == v) return u;
    // u parent of v

    for(int i = LOG - 1; i >= 0; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}

void solve(){
    int n, m; cin >> n;
    up.assign(n + 3, vector<int>(LOG));
    depth.assign(n, 0);
    for(int i = 0; i < n; ++i){
        int c; cin >> c;
        while(c--){
            int v; cin >> v;
            child[i].push_back(v);
        }
    }

    dfs(0);

    int q; cin >> q;
    while(q--){
        int u, v; cin >> u >> v;
        cout << LCA(u, v) << '\n';
    }

}  


int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
 
    //freopen("input.in","r",stdin);
    //freopen("output.out","w",stdout);
    
    int tc = 1; 
    bool multi = 0;
    if(multi) cin >> tc;

    while(tc--){
        solve();
    }
} 