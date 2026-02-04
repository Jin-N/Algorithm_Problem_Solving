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

    return 0;
}