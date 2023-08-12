#include <iostream>
using namespace std;

int main() {
  int N = 0, cnt = 0; cin >> N;
  for (int i = 0; i < N; i++) {
    int a; cin >> a;
    if ((i % 2) != (a % 2)) cnt += 1;
  }
  cout << min(cnt, N - cnt) << endl;
}
