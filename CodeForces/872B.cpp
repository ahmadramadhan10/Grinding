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
    int n, k; cin >> n >> k;
    vector<int>a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        st[0][i + 1] = a[i];
    }
    if(k == 2) {
        for(int i = 1; i <= K; ++i) {
            for(int j = 1; j + (1 << i) <= n + 1; ++j) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
        int ans = a[0];
        for(int i = 1; i < n; ++i) {
            int l = log2(i);
            int minimum = min(st[l][1], st[l][i - (1 << l) + 1]);
            ans = max(ans,minimum);
            l = log(n - i);
            minimum = min(st[l][i + 1], st[l][n - (1 << l) + 1]);
            ans = max(ans, minimum);
        }
        cout << ans;
    } else {
        sort(a.begin(), a.end());
        if(k == 1) {
            cout << a[0];
        } else {
            cout << a[n-1];
        }
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