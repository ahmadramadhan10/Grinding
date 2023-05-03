#include<bits/stdc++.h>
#define ll long long
#define log(x) 63 - __builtin_clzll(x)
using namespace std;

const ll MAXN = 262144;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
const ll K = 20;

int st[K][MAXN];

void solve(){
    int n, q; cin >> n >> q;
    vector<int>a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }
    while(q--) {
        int l, r, ans;
        cin >> l >> r;
        ans = a[r] ^ a[l - 1];
        cout << ans << '\n';
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