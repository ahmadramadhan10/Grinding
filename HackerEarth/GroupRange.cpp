#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAXN = 2e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

struct node{
    ll mx, mn;
};

int p[MAXN];
node val[MAXN];

int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}

void join(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return;
    p[x] = y;
    val[y].mx = max(val[y].mx, val[x].mx);
    val[y].mn = min(val[y].mn, val[x].mn);
}

void solve(){
    int n; cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> val[i].mx;
        val[i].mn = val[i].mx;
        p[i] = i;
    }
    int q; cin >> q;
    while(q--) {
        int u, v; cin >> u >> v;
        join(u, v);
        cout << val[find(u)].mn << " " << val[find(u)].mx << '\n';
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