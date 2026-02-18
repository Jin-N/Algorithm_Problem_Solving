#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
const int INF = 1e9;
const ll LINF = 4e18;
const ll MOD = 998244353; //1e9+7(다른 후보);

template<class T>
struct minPlus {
    static T linearComb(int i, int j,
                        const vector<vector<T>>& A,
                        const vector<vector<T>>& B,
                        int step){
        T MAX = numeric_limits<T>::max();
        T ans = MAX;
        int N = A.size();
        for(int k = 0; k < N; k++)
            ans = min(ans, A[i][k] == MAX || B[k][j] == MAX? MAX : A[i][k] + B[k][j]);  //overflow 방지
        return ans;
    }

    static vector<vector<T>> identity(int N) {
        T MAX = numeric_limits<T>::max();
        vector<vector<T>> I(N, vector<T>(N, MAX));
        for(int i = 0; i < N; i++) I[i][i] = 0;
        return I;
    }
};


template<class T>
struct normal {
    static T linearComb(int i, int j,
                        const vector<vector<T>>& A,
                        const vector<vector<T>>& B,
                        int step){
        T ans = 0;
        int N = A.size();
        for(int k = 0; k < N; k++)
            ans += A[i][k] + B[k][j]; 
        return ans;
    }

    static vector<vector<T>> identity(int N) {
        vector<vector<T>> I(N, vector<T>(N, 0));
        for(int i = 0; i < N; i++) I[i][i] = 1;
        return I;
    }
};

template<class T>
struct floydWarshall {
    static T linearComb(int i, int j,
                         const vector<vector<T>>& A,
                         const vector<vector<T>>& B,
                         int step) {
        assert(step != -1); 
        return min(A[i][j], A[i][k] + B[k][j]);
    }
};


/* minPlus, normal, floydWarshall 구조체 중 하나*/
// auto C = matMul<ll, normal<ll>>(A, B)
// auto C = matMul<ll, floydWarshall<ll>>(A, B, k)
template<class T, class SR>
vector<vector<T>> matMul(const vector<vector<T>>& A,
                        const vector<vector<T>>& B,
                        int step=-1) {
    int N = A.size();
    vector<vector<T>> C(N, vector<T>(N));
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            C[i][j] = SR::linearComb(i, j, A, B, step);
    return C;
}

/* matMul */
// auto C = matPow<ll, normal<ll>>(A, 2);   와 같은 식으로 사용
template<class T, class SR>
vector<vector<T>> matPow(vector<vector<T>> base, ll exp)
{
    int N = base.size();
    vector<vector<T>> ans = SR::identity(N);
    while (exp > 0) {
        if (exp & 1) ans = matMul<T, SR>(ans, base);
        base = matMul<T, SR>(base, base);
        exp >>= 1;
    }
    return ans;
}
