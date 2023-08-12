#include <iostream>
#include <vector>
#include <limits>
using namespace std ;
using ll = long long ;
int main() {
   int n ;
   cin >> n ;
   vector<ll> v(n) ;
   for (auto &vv:v)
      cin >> vv ;
   vector<ll> hiv(n) ;
   vector<ll> lov(n, numeric_limits<ll>::max()) ;
   for (int i=0; i<n; i++) {
      ll hi = 0 ;
      ll lo = lov[i] ;
      ll x = v[i] ;
      for (int j=i-1; j>=0; j--) {
         hi = max(hi, x + hiv[j]) ;
         lo = min(lo, x + lov[j]) ;
         x ^= v[j] ;
      }
      hiv[i] = max(hi, x) ;
      lov[i] = min(lo, x) ;
   }
   cout << hiv[hiv.size()-1] - lov[lov.size()-1] << endl ;
}
