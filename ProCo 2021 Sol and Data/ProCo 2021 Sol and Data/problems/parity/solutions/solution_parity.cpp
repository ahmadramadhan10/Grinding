#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    int N;
    cin >> N;

    int even_start = 0;
    for (int i = 0; i < N; i++){
        int n;
        cin >> n;
        if (n % 2 == 0 && i % 2 == 1) even_start++;
        if (n % 2 == 1 && i % 2 == 0) even_start++;
    }
    cout << min(N - even_start, even_start);
}