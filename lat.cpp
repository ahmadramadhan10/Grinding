#include<bits/stdc++.h>
#define int long long
#define el "\n"
using namespace std;

int a[1005], b[1005];

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int TC = 1; 
    //cin >> TC;

    while(TC--){
        int n, x; cin >> n >> x;
        for(int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        for(int i = 1; i <= n; ++i) {
            cin >> b[i];
        }

        vector<int>dp(x + 1); // dp sebelumnya
        int ans = 0;
        for(int i = 1; i <= n; ++i) {
            vector<int>cur_dp(x + 1);
            for(int j = 1; j <= x; ++j){
                if(j >= a[i]) {
                    cur_dp[j] = max(dp[j], dp[j - a[i]] + b[i]);
                } else {
                    cur_dp[j] = dp[j];
                }
            }
            dp = cur_dp;
            ans = max(ans, *max_element(dp.begin(), dp.end()));
        }
        cout << ans;
    }


    return 0;
}  