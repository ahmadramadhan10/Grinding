#include<bits/stdc++.h>
#define ll long long
using namespace std;

int N, M, Q; 

void update(int x, int y, ll val, vector<vector<ll>> &bit){
    for(int i = x; i <= N; i += i & (-i)) {
        for(int j = y; j <= M; j += j & (-j)) {
            bit[i][j] += val;
        }
    }
}

ll get_sum(int x, int y, vector<vector<ll>> & bit){
    ll ret = 0;
    for(int i = x; i; i -= i & (-i)){
        for(int j = y; j; j -= j & (-j)){
            ret += bit[i][j];
        }
    }
    return ret;
}

void solve(){
    cin >> N >> M >> Q;

    vector<vector<ll>>bit(N + 1, vector<ll>(M + 1, 0));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            ll val; cin >> val;
            update(i, j, val, bit);
        }
    }

    while(Q--) {
        int t; cin >> t;
        if(t == 1) {
            ll x, y, val; cin >> x >> y >> val;
            update(x, y, val, bit);
        } else {
            int a, b, c, d; cin >> a >> b >> c >> d;
            ll ans = get_sum(c, d, bit) + get_sum(a - 1, b - 1, bit) - get_sum(c, b - 1, bit) - get_sum(a - 1, d, bit);
            cout << ans << '\n';
        }
    }


}  

int32_t main(){
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