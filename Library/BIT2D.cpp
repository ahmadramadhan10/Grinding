
void update(int x, int y, ll val, vector<vector<ll>> &bit){
    for(int i = x; i <= N; i += i & (-i)) {
        for(int j = y; j <= M; j += j & (-j)) {
            bit[i][j] += val;
        }
    }
}

ll get_sum(int x, int y, vector<vector<ll>> & bit){
    ll ret = 0;
    for(int i = x; i; i -= i & (-i)){
        for(int j = y; j; j -= j & (-j)){
            ret += bit[i][j];
        }
    }
    return ret;
}