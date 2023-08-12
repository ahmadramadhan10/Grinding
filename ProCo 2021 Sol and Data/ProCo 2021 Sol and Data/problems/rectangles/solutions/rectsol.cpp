#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair < pair <int, int > , pair <int, int> > piiii;

#define ff first
#define ss second

const int MAXN = 200005;
int n, st[4*MAXN], lazy[4*MAXN];

void update(int v, int tl, int tr, int l, int r, int x) {
    if(lazy[v] != 0) {
        st[v] += lazy[v];
        if(tl != tr) {
            lazy[v<<1] += lazy[v];
            lazy[v<<1|1] += lazy[v];
        }
        lazy[v] = 0;
    }

    if(tl > r || tr < l || l > r) {
        return;
    }

    if(l <= tl && tr <= r) {
        st[v] += x;
        if(tl != tr) {
            lazy[v<<1] += x;
            lazy[v<<1|1] += x;
        }
        return;
    }

    int tm = (tl + tr)/2;
    update(v<<1, tl, tm, l, r, x);
    update(v<<1|1, tm+1, tr, l, r, x);
    st[v] = max(st[v<<1], st[v<<1|1]);
}

int query(int v, int tl, int tr, int l, int r) {
    if(l > r || tl > r || tr < l) {
        return INT_MIN;
    }
    if(lazy[v] != 0) {
        st[v] += lazy[v];
        if(tl != tr) {
            lazy[v<<1] += lazy[v];
            lazy[v<<1|1] += lazy[v];
        }
        lazy[v] = 0;
    }

    if(l <= tl && tr <= r) {
        return st[v];
    }

    int tm = (tl + tr)/2;
    return max(query(v<<1, tl, tm, l, r), query(v<<1|1, tm+1, tr, l,r));
}

int N,M,K;
vector<pii> G;

map<int,int> xcomp;
map<int,int> ycomp;

int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);

  cin >> N >> M >> K;
  G.resize(M);
  for (int i = 0; i < M; i++) {
    cin >> G[i].ff >> G[i].ss;
  }
  set<int> xcoords;
  set<int> ycoords;
  for (int i = 0; i < M; i++) {
      xcoords.insert(G[i].ff);
      xcoords.insert(G[i].ff + K);
      ycoords.insert(G[i].ss);
      ycoords.insert(G[i].ss + K-1);
  }
  int xval = 0;
  int yval = 0;
  for(int x : xcoords) {
    xcomp[x] = xval;
    xval++;
  }
  for(int y : ycoords) {
    ycomp[y] = yval;
    yval++;
  }
  vector<piiii> segs(2*M);

  for (int i = 0; i < M; i++) {
    segs[2*i] = {{xcomp[G[i].ff], ycomp[G[i].ss]}, {ycomp[G[i].ss + K-1], 1}};
    segs[2*i+1] = {{xcomp[G[i].ff+K], ycomp[G[i].ss]}, {ycomp[G[i].ss + K-1], -1}};
  }
  sort(segs.begin(), segs.end());

  int ans = 0;

  for(int i = 0; i < 2*M; i++) {
    if(i != 0 && segs[i].ff.ff != segs[i-1].ff.ff) ans = max(ans, query(1, 0, yval, 0, yval));
    update(1, 0, yval, segs[i].ff.ss, segs[i].ss.ff, segs[i].ss.ss);
  }

  cout << ans << endl;
}
