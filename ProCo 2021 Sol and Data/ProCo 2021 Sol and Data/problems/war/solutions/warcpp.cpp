#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int N = 0; cin >> N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }
  sort(A.begin(), A.end(), greater<int>());
  sort(B.begin(), B.end(), greater<int>());
  int ans = 0;
  int ptr = 0;

  for (int i = 0; i < N; i++) {
    while(ptr < N && A[i] < B[ptr]) {
      ptr++;
    }
    if(ptr < N && A[i] > B[ptr]) {
      ans++;
      ptr++;
    }
  }
  cout << ans << endl;
}
