n = int(input())
hi = 0
lo = 0
for i in range(n):
    v = int(input())
    hi += v
    lo ^= v
print(hi - lo)
