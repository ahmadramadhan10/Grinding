#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll W, S;
int k;
ll a[5001];
ll dp[5001][5001];

ll go(int now, int stk){
	if(now==n){
		return 0LL;
	}
	if(stk==k){
		stk = 0;
	}
	if(dp[now][stk]>=0LL){
		return dp[now][stk];
	}
	if(stk==0LL){
		ll ret = a[now] + go(now+1,0);
		ret = min(ret,W+go(now+1,1));
		dp[now][stk] = ret;
	}
	else{
		int l = stk;
		int r = k-stk;
		ll ret = S*(ll)min(l,r) + a[now] + go(now+1,stk);
		ret = min(ret, go(now+1,stk+1));
		dp[now][stk] = ret;
	}
	return dp[now][stk];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	cin >> W >> S;
	for(int i = 0; i<n; i++){
		cin >> a[i];
	}
	for(int i = 0; i<=n; i++){
		for(int j = 0; j<=n; j++){
			dp[i][j] = -1LL;
		}
	}
	cout << go(0,0) << endl;
}