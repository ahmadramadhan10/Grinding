#include <iostream>
#include <string>
using namespace std ;
int n ;
const int MAXN = 10 ;
const int ARRSZ = 2 * MAXN + 2 ;
int adj[ARRSZ][ARRSZ] ;
int addbox(int x, int y) {
   return ++adj[x][y] == 4 ;
}
int main() {
   cin >> n ;
   int mvcnt = 2*n*(n-1) ;
   int score1=0, score2=0 ;
   string who ;
   char hero = 'A' ;
   char opp = 'B' ;
   for (int i=0; i<mvcnt; i++) {
      who.push_back(hero) ;
      int x1, y1, x2, y2 ;
      cin >> x1 >> y1 >> x2 >> y2 ;
      int thisturn = 0 ;
      thisturn += addbox(x1+x2+y1-y2, y1+y2+x1-x2) ;
      thisturn += addbox(x1+x2+y2-y1, y1+y2+x2-x1) ;
      score1 += thisturn ;
      if (thisturn == 0) {
         swap(score1, score2) ;
         swap(hero, opp) ;
      }
   }
   cout << who << endl ;
   if (hero == 'A')
      cout << score1 << " " << score2 << endl ;
   else
      cout << score2 << " " << score1 << endl ;
}
