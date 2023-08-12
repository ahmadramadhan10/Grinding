#include <iostream>
#include <string>
#include <vector>
using namespace std ;
using ll = long long ;
using ull = unsigned long long ;
const int MAXB = 4 * 1024 * 1024 ;
const int SH = 7 ;
const int MASK = (1 << SH) - 1 ;
char b[MAXB] ;
ull seen[MAXB][4] ;
signed short dirlim[MAXB][4] ;
int dd[4] ;
int n, m, hi ;
int off(int i, int j) {
   return (i + 1) * (m + 1) + j ;
}
void chase(int i, int j, int di, int cnt) {
   int p = off(i, j) ;
   int mlen = 0 ;
   int dp = -dd[di] ;
   for (int k=0; k<cnt; k++, p += dp) {
      if (b[p])
         mlen = -1 ;
      dirlim[p][di] = mlen ;
      mlen++ ;
   }
}
int main() {
   cin >> n >> m ;
   dd[0] = 1 ;
   dd[1] = -1 ;
   dd[2] = m + 1 ;
   dd[3] = - m - 1 ;
   hi = (m + 1) * (n + 2) ;
   fill(b, b+sizeof(b)/sizeof(b[0]), 1) ;
   for (int i=0; i<n; i++) {
      string s ;
      cin >> s ;
      for (int j=0; j<m; j++)
         b[off(i,j)] = s[j] - '0' ;
   }
   for (int i=0; i<n; i++) {
      chase(i, m-1, 0, m) ;
      chase(i, 0, 1, m) ;
   }
   for (int j=0; j<m; j++) {
      chase(n-1, j, 2, n) ;
      chase(0, j, 3, n) ;
   }
   vector<ull> lev, nlev ;
   int maxspeed = 1 ;
   while (maxspeed * (maxspeed + 1) / 2 <= max(n, m))
      maxspeed++ ;
   seen[0][2] = 1 ;
   lev.push_back((off(0, 0) << (SH + 2)) + 2) ;
   int r = -1 ;
   if (n == 1 && m == 1) {
      r = 0 ;
      goto done ;
   }
   for (ll d=0; lev.size(); d++) {
      for (auto s: lev) {
         int olddir = s & 3 ;
         s >>= 2 ;
         int pos = s >> SH ;
         int speed = s & MASK ;
         for (int dir=0; dir<4; dir++) {
            if (speed != 0 && dir != olddir)
               continue ;
            for (int nspeed=speed-1; nspeed<=speed+1; nspeed++) {
               int npos = pos + nspeed * dd[dir] ;
               if ((nspeed != speed && dir != olddir) ||
                   nspeed < 0 || nspeed > maxspeed ||
                   (nspeed == speed && nspeed != 0) ||
                   nspeed > dirlim[pos][dir] ||
                   ((seen[npos][dir] >> nspeed) & 1))
                  continue ;
               if (npos == off(n-1, m-1)) {
                  r = d+1 ;
                  goto done ;
               }
               seen[npos][dir] |= 1LL << nspeed ;
               nlev.push_back((((npos << SH) + nspeed) << 2) + dir) ;
            }
         }
      }
      swap(lev, nlev) ;
      nlev.clear() ;
   }
done:
   cout << r << endl ;
}
