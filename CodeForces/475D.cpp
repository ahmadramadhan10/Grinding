#include<bits/stdc++.h>
#define ll long long
#define log(x) 63 - __builtin_clzll(x)
using namespace std;

const ll MAXN = 262144;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
const ll K = 20;

int gcd(int a, int b) {
    return __gcd(a,b);
}

void solve(){
    int n; cin >> n;
    vector<int>a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    map<ll,ll>div, temp, query;
    for(int i = 0; i < n; ++i) {
        temp.clear();
        for(auto cur : div) {
            temp[gcd(cur.first, a[i])] += cur.second;
        }
        temp[a[i]]++;
        swap(div,temp);
        for(auto cur : div) {
            query[cur.first] += cur.second;
        }
    }

    int q; cin >> q;
    while(q--) {
        int x; cin >> x;
        cout << query[x] << '\n';
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