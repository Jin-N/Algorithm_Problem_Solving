#include <bits/stdc++.h>
using namespace std;


// spf[i]: i의 smallest prime factor    expo[i]: i의 소인수분해 결과에서 spf[i]가 갖는 지수
// nxt[i]: i/(power(spf[i], expo[i]))   primes[i]: 소수를 순서대로 담은 배열
// auto [spf, expo, nxt, primes] = buildSpf(N); 과 같은 식으로 이용
auto buildSpf(int N){
    vector<int> spf(N+1);       // 아래 if(!spf[i]) 조건문 발동을 위해 0으로 초기화
    vector<int> expo(N+1, 1);   // 아래 else문에서 expo 갱신 생략을 위해 1로 초기화
    vector<int> nxt(N+1, 1);
    vector<int> primes;

    for(int i=2; i<=N; i++){
        if(!spf[i]){
            spf[i] = i;
            expo[i] = 1;
            nxt[i] = 1;
            primes.push_back(i);
        }
        for(int p : primes){    // linear Sieve
            int mul = i*p;
            if(p > spf[i] || mul > N) break;
            spf[mul] = p;
            if(p == spf[i]){
                expo[mul] = expo[i] + 1;
                nxt[mul] = nxt[i];
            }
            else
                nxt[mul] = i;
        }
    }
    return tuple{spf, expo, nxt, primes};
}