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
    int N, K, X;
    cin >> N >> K >> X;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];
    sort(all(A));
    vector<ll> diff(N-1);
    rep(i, 0,N-1) diff[i] = A[i] - A.back();

    //최소힙 pq와 unordered_set visited 를 만든다.
    //pq에는 {지금까지의 차분의 총합, (길이 N-1짜리 갯수 정보)}이 들어간다.
    //visited에는 (길이 N-1짜리 갯수 정보)가 들어간다.
    //초기에 pq에 {A[0], (1, 0, 0.....)} ~ {A[N-2], (0, 0, ....1)}를 넣는다.
    //visited에도 넣는다.
    //이후 한개씩 꺼내면서 N-1개의 자식들(각 과자를 1개씩 더한 것)을 visited에 없는지 검사하고 pq에 넣는다.
    //A.back()*X - 꺼낸 것의 first 를 출력한다. 

    priority_queue<pair<ll, vector<ll>>> pq;
    pq.push({0, vector<ll>(N-1, 0)});
    set<vector<ll>> visited;
    visited.insert(vector<ll>(N-1, 0));

    vector<ll> ans;
    rep(_, 0, X){
        auto [sumDiff, cnt] = pq.top(); pq.pop();
        ans.push_back(A[N-1]*K + sumDiff);

        if(accumulate(all(cnt), 0) == K) continue;
        rep(i, 0, N-1){
            vector<ll> nxt = cnt;
            nxt[i]++;
            if(!visited.count(nxt)){
                visited.insert(nxt);
                pq.push({sumDiff+diff[i], nxt});
            }
        }
    }

    for(auto val : ans) cout << val << '\n';
    return 0;
}