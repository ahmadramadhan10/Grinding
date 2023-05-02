#include<bits/stdc++.h>
#define ll long long
#define log(x) 63 - __builtin_clzll(x)
using namespace std;

const ll MAXN = 262144;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
const ll K = log(MAXN);

int st[K + 1][MAXN];

void solve(){
    int n, q; cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> st[0][i];
    }
    for(int i = 1; i <= K; ++i) {
        for(int j = 1; j + (1 << i) <= n + 1; ++j) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }

    cin >> q;
    while(q--) {
        int l, r; cin >> l >> r;
        l++, r++;
        int lg = log(r-l+1);
        cout << min(st[lg][l], st[lg][r - (1 << lg) + 1]) << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int TC = 1; 
    //cin >> TC;
    while(TC--) {
        solve();
    }
    
    return 0;
} 