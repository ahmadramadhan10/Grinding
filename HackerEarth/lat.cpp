#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAXN = 2e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

struct node{
    ll x, y, cost;
};

int p[1009];
node d[1009];

int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}

void join(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) return;
    p[x] = y;   
}

bool same(int x, int y) {
    return find(x) == find(y);
}
void solve(){
    int n; cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i].x >> d[i].y;
        d[i].cost = 0;
        p[i] = i;
    }
    for(int i = 1; i <= n; ++i) {
        ll cost_min = inf;
        int node = -1;
        for(int j = i + 1; j <= n; ++j) {
            ll x = abs(d[i].x - d[j].x);
            ll y = abs(d[i].y - d[j].y);
            if(x * x + y * y < cost_min) {
                cost_min = x * x + y * y;
                node = j;
            }
        }
        if(node != -1) {
            if(same(i,node)) continue;
            join(i,node);
            int par = find(i);
            d[par].cost += cost_min;
        }
    }
    cout << d[find(1)].cost;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int TC = 1;
    //cin >> TC;
    while(TC--){
        solve();
    }
}