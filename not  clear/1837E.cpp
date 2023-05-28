#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const ll N = 1e6 + 9;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
const ll LOG = 20;

template<typename T>
void min_self(T &a, T b) {
	a = min(a,b);
}

template<typename T>
void max_self(T &a, T b) {
	a = max(a,b);
}

template<typename T>
void add(T &a, T b){
	a += b;
	if(a >= mod) a -= mod;
}

/*
idenya bahwa yang paling bawah rank 2^(k - 1) + 1 --> 2^k harus nyebar
trus lanjutkan ke layer selanjutnya bawah 2 ^(k' - 1) + 1 --> 2^k' 
harus nyebar, k' = k - 1; -> k akan turun sampai 
binary lifting 

*/
long long fc[N + 5], ifc[N + 5];

long long modpow(ll a, ll b){
	ll res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		b >>= 1;
		a = a * a % mod;
	} 
	return res;
}

void init(){
	fc[0] = 1;
	for(int i = 1; i <= N; ++i) {
		fc[i] = fc[i - 1] * 1LL * i % mod;
	}
	ifc[N] = modpow(fc[N], mod - 2);
	for(int i = N - 1; i >= 0; i--) {
		ifc[i] = 1LL * (i + 1LL) * ifc[i + 1] % mod;
	}
}

void solve(){
	int k; cin >> k;
	int sz = (1 << k) + 1;
	vector<int>a(sz + 1);
	vector<bool>resereve(sz + 1);
	vector<int>p(sz, -1);
	int cur = 0;
	for(int i = 1; i <= (1 << k); ++i) {
		cin >> a[i];
		resereve[a[i]] = (a[i] != -1); // is true when a[i] is reserved
		if(a[i] != -1) { // reserve;
			if(i & 1) cur++;
			p[i] = cur;
		}
	}
	long long ans = 1;
	for(int i = k; i >= 0; i--) {
		set<int>st;
		int cnt = 0;
		for(int j = (1 << k); j > (1 << (k - 1)); --j){
			if(p[j] != -1) { // reserved;
				st.insert(p[j]);
				cnt++;
			}
		}
		if(st.size() != cnt) { // berarti ada memiliki parent yg sama atau dalam bracket yg sama
			cout << 0 << '\n';
			return;
		}
		int tot = 1 << (k - 1);
		ans = ans * fc[tot] * ifc[cnt] % mod;
	}
	
}   
 
int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	init();
	int tc = 1;
	cin >> tc;
	while(tc--) {
		solve();
	}
} 
/*
-if stuck, start thinking backwards, may be you got some solution 
*/