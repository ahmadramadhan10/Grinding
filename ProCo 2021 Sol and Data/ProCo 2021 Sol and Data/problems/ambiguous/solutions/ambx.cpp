#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
typedef vector<int> vi;
#define f first
#define s second
// END NO SAD

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<ll>> matrix;

map<int, int> dp;
int child[1000005];
vector<int> edges[1000005];
int layer[1000005];
int maxto[1000005];
int amtatlayer[1000005];
bool good[1000005];

void solve() {
  int n, m;
  cin >> n >> m;
  while(m--) {
    int a, b;
    cin >> a >> b;
    edges[a].pb(b);
    child[b]++;
  }
  vector<int> topo;
  topo.reserve(n);
  for(int i = 1; i <= n; i++) {
    if(child[i] == 0) {
      topo.pb(i);
      layer[i] = 1;
      amtatlayer[1]++;
    }
  }
  for(int i = 0; i < sz(topo); i++) {
    int curr = topo[i];
    for(int out: edges[curr]) {
      if(--child[out] == 0) {
        amtatlayer[layer[out] = layer[curr] + 1]++;
        topo.pb(out);
      }
    }
  }
  assert(sz(topo) == n);
  int highest = 0;
  for(int i = 0; i < sz(topo);) {
    int j = i+1;
    while(j < n && layer[topo[i]] == layer[topo[j]]) j++;
    if(j-i == 1 && highest <= layer[topo[i]]) good[topo[i]] = true;
    for(int k = i; k < j; k++) {
      int minseen = 1e9;
      for(int out: edges[topo[k]]) minseen = min(minseen, layer[out]);
      highest = max(highest, minseen);
    }
    i = j;
  }
  int ret = 0;
  for(int i = 1; i <= n; i++) {
    ret += !good[i];
  }
  cout << n - ret << "\n";
}

// !editcommand?
// are there edge cases (N=1?)
// are array sizes proper (scaled by proper constant, for example 2* for koosaga tree)
// integer overflow?
// DS reset properly between test cases
// are you doing geometry in floating points
// are you not using modint when you should

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  solve();
}
