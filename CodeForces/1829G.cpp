#include<bits/stdc++.h>
#define ll long long
#define log(x) 63 - __builtin_clzll(x)
using namespace std;

const ll MAXN = 262144;
const ll mod = 1e9 + 7;
const ll inf = 2e9;
const ll LOG = 19;

ll f[1509][1509];
pair<int,int>dg[1500];

void solve(){
	ll n; cin >> n;
	auto sigma = [](ll x){
		return x * (x + 1) / 2;
	};

	ll l = 1, r = 1500, mid, best = 1;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(sigma(mid) <= n) {
			best = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	if(sigma(best) < n) { // jika 
		best++;
	}
	l = dg[best].first;
	int sel = n - l;
	int row = dg[best].second - sel;
	int col = sel + 1;
	cout << f[row][col] << '\n';
	//best udah tau, sisa tau d;ia di column ke berapa
}  

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

	ll cur = 1;
	ll inc = 1;
	ll dia = inc;
	int N = 1450;
	for(int i = 1; i <= N; ++i) {
		ll temp = cur;
		dg[i] = {cur, dia};
		for(int j = 1; j <= dia; ++j) {
			f[dia - j + 1][j] = temp * temp;
			if(temp > 1e6) {
				break;
			}
			temp++;
		}
		cur += inc;
		inc++;
		dia = inc;
	}
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
		}
	}


	int tc = 1; 
	cin >> tc;
	while(tc--) {
		solve();
	}
    return 0;
} 