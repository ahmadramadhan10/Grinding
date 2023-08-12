#include <iostream>
#include <vector>
#include <map>
using namespace std ;
using ll = long long ;
int main() {
   ll n ;
   cin >> n ;
   vector<ll> v(n) ;
   for (auto &vv: v)
      cin >> vv ;
   ll s = 0 ;
   for (auto vv: v)
      s += vv ;
   s /= n ;
   for (auto &vv: v)
      vv -= s ;
   map<ll, int> cnts ;
   s = 0 ;
   for (auto vv: v) {
      s += vv ;
      cnts[s]++ ;
   }
   int r = 1 ;
   for (auto it: cnts)
      r = max(r, it.second) ;
   cout << n-r << endl ;
}
