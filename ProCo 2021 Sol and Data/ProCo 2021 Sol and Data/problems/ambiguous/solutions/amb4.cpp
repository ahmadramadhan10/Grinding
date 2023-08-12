#include <iostream>
#include <vector>
using namespace std ;
vector<vector<int>> edgesf, edgesb ;
int n, m ;
vector<int> x(const vector<vector<int>> &edgesf, const vector<vector<int>> &edgesb) {
   vector<int> indeg(n) ;
   for (int i=0; i<n; i++)
      indeg[i] = edgesb[i].size() ;
   vector<int> ready ;
   for (int i=0; i<n; i++)
      if (!edgesb[i].size())
         ready.push_back(i) ;
   vector<int> frontier(n, 0) ;
   vector<int> r(n, -1) ;
   int frontsize = 0 ;
   int above = 0 ;
   while (ready.size()) {
      int a = ready[ready.size()-1] ;
      ready.pop_back() ;
      if (!ready.size()) {
         int fronttouch = 0 ;
         for (auto b: edgesb[a])
            if (frontier[b] == 0)
               fronttouch++ ;
         if (fronttouch == frontsize)
            r[a] = above ;
      }
      for (auto b: edgesb[a]) {
         if (frontier[b] == 0)
            frontsize-- ;
         frontier[b]++ ;
      }
      for (auto b: edgesf[a])
         if (--indeg[b] == 0)
            ready.push_back(b) ;
      above++ ;
      frontsize++ ;
   }
   return r ;
}
int main() {
   cin >> n >> m ;
   edgesf.resize(n) ;
   edgesb.resize(n) ;
   for (int i=0; i<m; i++) {
      int a, b ;
      cin >> a >> b ;
      a-- ;
      b-- ;
      edgesf[a].push_back(b) ;
      edgesb[b].push_back(a) ;
   }
   auto above = x(edgesf, edgesb), below = x(edgesb, edgesf) ;
   int cnt = 0 ;
   for (int i=0; i<n; i++)
      if (above[i] + below[i] + 1 != n)
         cnt++ ;
   cout << n - cnt << endl ;
}
