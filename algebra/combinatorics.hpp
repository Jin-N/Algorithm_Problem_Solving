#include <bits/stdc++.h>
using namespace std;

// MOD가 소수, a < MOD일 때에만 유효. 
// MOD > 3e+9 면 overflow 가능성 있음.
long long modPow(long long a, long long e, const long long MOD){
    long long ans = 1;
    a %= MOD;
    e %= MOD-1;
    if(e<0)
        e = (-e)*(MOD-2)%(MOD-1);
    while(e){
        if(e&1) ans = ans*a%MOD;
        a = a*a%MOD;
        e >>= 1;
    }
    return ans;
}

/* modPow */
// n까지 팩토리얼과 역팩토리얼 배열을 참조로 반환
pair<vector<long long>, vector<long long>> factorials(long long n, const long long MOD) {
    vector<long long> fact(n+1, 1), invFact(n+1, 1);
    // 팩토리얼 계산
    for (long long i = 1; i <= n; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    // invFact[n]만 역원 계산
    invFact[n] = modPow(fact[n], -1, MOD);
    for (long long i = n; i > 0; --i)
        invFact[i - 1] = invFact[i] * i % MOD;

    return {fact, invFact};
}

// 조합 계산: nCk = fact[n] * invFact[k] * invFact[n-k] % p
long long comb(long long n, long long k, long long p,
               const vector<long long>& fact, 
               const vector<long long>& invFact) {
    assert(0 <= k && k <= n);  // 범위 벗어나면 런타임 에러

    long long ans = 1;
    while(n || k){
        long long ni = n%p;
        long long ki = k%p;
        if(ki > ni) return 0;
        ans = ans * fact[ni] % p * invFact[ki] % p * invFact[ni - ki] % p;
        n /= p;
        k /= p;
    }
    return ans;
}