#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std ;
using ll = long long ;
int n ;
vector<ll> tips ;
vector<int> leg, len ;
vector<vector<int>> edges ;
vector<int> chase(int pred, int a, int id) {
   vector<int> r ;
   while (1) {
      r.push_back(a) ;
      leg[a] = id ;
      if (edges[a].size() <= 1)
         break ;
      for (auto b: edges[a])
         if (b != pred) {
            pred = a ;
            a = b ;
            break ;
         }
   }
   reverse(r.begin(), r.end()) ;
   return r ;
}
ll r = 0 ;
int bx, by ;
void consider(ll score, int nx, int ny, const char *wh) {
   if (score < r)
      return ;
   if (nx > ny)
      swap(nx, ny) ;
   if (score > r || (score == r && (nx < bx || (nx == bx && ny < by)))) {
      r = score ;
      bx = nx ;
      by = ny ;
   }
}
vector<pair<ll, int>> lin(const vector<int> vp) {
   int n = vp.size() ;
   vector<pair<ll, int> > s ;
   for (int i=0; i<n; i++) {
      int vv = tips[vp[i]] ;
      int b = i ;
      while (s.size() && vv < s[s.size()-1].first) {
         consider(s[s.size()-1].first * (i - s[s.size()-1].second),
                  vp[s[s.size()-1].second], vp[i-1], "A") ;
         b = s[s.size()-1].second ;
         s.pop_back() ;
      }
      if (!s.size() || s[s.size()-1].first != vv)
         s.push_back({vv, b}) ;
   }
   for (int i=0; i<(int)s.size(); i++)
      consider(s[i].first * (n - s[i].second), vp[s[i].second], vp[n-1], "B") ;
   for (auto &v:s) {
      len[vp[v.second]] = n - v.second ;
      v.second = vp[v.second] ;
   }
   return s ;
}
ll encode(int np) {
   return (((ll)len[np]) << 20) + (1000000 - np) ;
}
int declen(ll v) {
   return (v >> 20) ;
}
int main() {
   cin >> n ;
   tips.resize(n) ;
   len.resize(n) ;
   leg.resize(n) ;
   for (auto &vv : tips)
      cin >> vv ;
   vector<pair<ll, int>> sortme ;
   for (int i=0; i<(int)tips.size(); i++)
      sortme.push_back({tips[i], i}) ;
   sort(sortme.begin(), sortme.end()) ;
   edges.resize(n) ;
   for (int i=1; i<n; i++) {
      int a, b; 
      cin >> a >> b ;
      a-- ;
      b-- ;
      edges[a].push_back(b) ;
      edges[b].push_back(a) ;
   }
   int root = 0 ;
   for (int i=0; i<n; i++)
      if (edges[i].size() > edges[root].size())
         root = i ;
   leg[root] = -1 ;
   bx = root ;
   by = root ;
   r = tips[root] ;
   set<pair<ll, int>> hep ;
   vector<vector<pair<ll, int>>> stacks ;
   for (int i=0; i<(int)edges[root].size(); i++) {
      int b = edges[root][i] ;
      auto np = chase(root, b, i) ;
      // increasing tips, node ids by decreasing length
      auto st = lin(np) ;
      reverse(st.begin(), st.end()) ;
      stacks.push_back(st) ;
      hep.insert({encode(st[st.size()-1].second), i}) ;
   }
   int tipi = 0 ;
   int changed = 1 ;
   while (hep.size()) {
      if (changed) {
         auto t1 = hep.rbegin() ;
   // heap is length,leg#
   // stacks are decreasing tips, node-id by increasing length
         auto &s1 = stacks[t1->second] ;
         auto t2 = t1 ;
         t2++ ;
         if (t2 == hep.rend()) {
            consider(min(tips[root], s1[s1.size()-1].first) * (1 + declen(t1->first)),
                     s1[s1.size()-1].second, root, "C") ;
         } else {
            auto &s2 = stacks[t2->second] ;
            consider(min(tips[root], min(s1[s1.size()-1].first, s2[s2.size()-1].first)) *
              (1 + declen(t1->first) + declen(t2->first)),
               s1[s1.size()-1].second, s2[s2.size()-1].second, "D") ;
         }
      }
      changed = 0 ;
      while (1) {
         if (tipi >= n)
            goto done ;
         ll tt = sortme[tipi].first ;
         int p = sortme[tipi++].second ;
         if (leg[p] < 0)
            continue ;
         auto &s3 = stacks[leg[p]] ;
         if (!s3.size())
            continue ;
         if (s3[s3.size()-1].first == tt) {
            hep.erase({encode(s3[s3.size()-1].second), leg[p]}) ;
            s3.pop_back() ;
            if (s3.size())
               hep.insert({encode(s3[s3.size()-1].second), leg[p]}) ;
            changed = 1 ;
            break ;
         }
      }
   }
done:
   cout << r << endl << bx+1 << " " << by+1 << endl ;
}
