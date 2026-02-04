#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
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

void init() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    init();
    unsigned N, Q;
    cin >> N >> Q;

    struct value { unsigned long max; unsigned up, down; };
    struct op { unsigned flip; unsigned long add; };
    atcoder::lazy_segtree<value,
                          [](const value lhs, const value rhs) { return value{max(lhs.max, rhs.max), lhs.up + rhs.up, lhs.down + rhs.down}; },
                          [] { return value{}; },
                          op,
                          [](const op operation, const value segment) {
                              return value{
                                  (operation.flip & 1 ? segment.down : segment.up) ? operation.flip ? operation.add : segment.max + operation.add : 0,
                                  operation.flip & 1 ? segment.down : segment.up,
                                  operation.flip & 1 ? segment.up : segment.down
                              };
                          },
                          [](const op lhs, const op rhs) { return op{lhs.flip + rhs.flip, (lhs.flip ? 0 : rhs.add) + lhs.add}; },
                          [] { return op{}; }> segment_tree(vector(N, value{0, 1, 0}));

    for (unsigned q{}; q < Q; ++q) {
        unsigned t;
        cin >> t;
        if (t == 1) {
            unsigned L, R, X;
            cin >> L >> R >> X;
            segment_tree.apply(L - 1, R, op{0, X});
        } else if (t == 2) {
            unsigned L, R;
            cin >> L >> R;
            segment_tree.apply(L - 1, R, op{1, 0});
        } else {
            unsigned L, R;
            cin >> L >> R;
            cout << segment_tree.prod(L - 1, R).max << endl;
        }
    }
    return 0;
}