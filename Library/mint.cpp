int mod = 998244353;
 
struct mint {
    int value = 0;
 
    constexpr mint() : value() {}
 
    mint(const long &x) {
        value = normalize(x);
    }
 
    static long normalize(const long &x) {
        long v = x % mod;
        if (v < 0) v += mod;
        return v;
    }
 
    bool operator==(const mint &x) { return value == x.value; };
 
    mint operator+(const mint &x) { return value + x.value; };
 
    mint operator-(const mint &x) { return value - x.value; };
 
    mint operator*(const mint &x) { return (long) value * x.value; };
 
    void operator+=(const mint &x) { value = normalize(value + x.value); };
 
    void operator-=(const mint &x) { value = normalize(value - x.value); };
};
 
mint power(mint a, long b) {
    mint res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}
 
mint inv(mint a) {
    return power(a, mod - 2);
}