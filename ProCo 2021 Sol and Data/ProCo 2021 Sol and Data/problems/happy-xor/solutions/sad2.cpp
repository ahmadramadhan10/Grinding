#include <iostream>
#include <vector>
#include <limits>
using namespace std ;
using ll = long long ;
int main() {
   int n ;
   cin >> n ;
   ll hi = 0, lo = 0 ;
   for (int i=0; i<n; i++) {
      ll v ;
      cin >> v ;
      hi += v ;
      lo ^= v ;
   }
   cout << hi - lo << endl ;
}
