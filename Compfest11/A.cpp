#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAXN = 2e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

struct segment{
    ll l, r;
};

bool cmp(segment x, segment y) {
    if(x.l == y.l) {
        return x.r < y.r;
    } else {
        return x.l < y.l;
    }
}

void solve(){
    int n; cin >> n;
    vector<segment>s(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i].l >> s[i].r;
    }
    sort(s.begin(), s.end(), cmp);
    auto sum = [](ll x) {
        return x * (x + 1) / 2LL;
    };

    ll l = s[0].l, r = s[0].r, ans = 0;
    ans = sum(r) - sum(l - 1);
    //cout << ans << '\n';
    for(int i = 1; i < n; ++i) {
        if(s[i].r <= r) continue;
        if(s[i].l >= r) {
            if(s[i].l == r) l = s[i].l + 1;
            else l = s[i].l;
            r = s[i].r;
            ans += sum(r) - sum(l - 1);
        }  else {
            l = r + 1;
            r = s[i].r;
            ans += sum(r) - sum(l - 1);
        }
      //  cout << ans << '\n';
    }
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int TC = 1;
    //cin >> TC;
    while(TC--){
        solve();
    }
}