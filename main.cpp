#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

const int INF = 1e9;
const ll LINF = 4e18;
const int MOD = 1e9+7;

#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define all(x) (x).begin(), (x).end()

template<class T>
void chmax(T &a, T b) { if (a < b) a = b; }

template<class T>
void chmin(T &a, T b) { if (a > b) a = b; }

template<class A, class B>
ostream& operator<<(ostream& os, const pair<A,B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << '[';
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) os << ", ";
        os << v[i];
    }
    return os << ']';
}


void init() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    init();

    int N, Q;
    cin >> N >> Q;
    set<ll> forbidden;
    rep(i, 0, N){
        int x; cin >> x;
        forbidden.insert(x);
    }
    vector<ll> A(all(forbidden));   // 중복되는 forbidden은 무의미함.
    vector<pll> increment; // {a, b}가 들어있다면, 1부터 forbidden제외 누적갯수가 b개인 수 중에서 최소가 a다.
    if(A[0] != 1) increment.push_back({1, 1});
    rep(i, 0, A.size())
        if(i == A.size()-1 || A[i]+1 != A[i+1]) 
            increment.push_back({A[i]+1, A[i]-i});
                 
    while(Q--){
        // f(m) = k 일 때, 1부터 m까지의 수 중 forbidden을 제외한 갯수가 k다.
        // f(x) = t 이고, x가 forbidden에 속한다면, f(ans) = t+y 이고, ans는 이 조건을 만족하는 수 중 최소다. 
        // f(x) = t 이고, x가 forbidden에 속하지 않는다면, f(ans) = t+y-1 이고, ans는 이 조건을 만족하는 수 중 최소다. 

        int X, Y;
        cin >> X >> Y;
        int idx = upper_bound(all(increment), pll(X, LINF)) - increment.begin() - 1;
        ll t, target;
        if(forbidden.count(X)){
            t = increment[idx+1].second - 1;
            target = t + Y;
        }
        else{
            t = increment[idx].second + X - increment[idx].first;
            target = t + Y - 1;
        }
        int j = upper_bound(all(increment), target, [](const ll& val, const pll& p){
            return val < p.second;
            }) - increment.begin() - 1;
        int ans = increment[j].first + (target - increment[j].second);

        cout << ans << '\n';
    }
    return 0;
}