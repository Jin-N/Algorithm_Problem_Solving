#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

const int INF = 1e9;
const ll LINF = 4e18;
const ll MOD = 998244353; //1e9+7(다른 후보);

#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define all(x) (x).begin(), (x).end()

template<class T>
void chmax(T &a, T b) { if (a < b) a = b; }

template<class T>
void chmin(T &a, T b) { if (a > b) a = b; }


struct custom_hash {
    // ===== splitmix64 (anti-hash attack) =====
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    // 실행마다 다른 seed
    static uint64_t fixed_random() {
        static const uint64_t seed =
            chrono::steady_clock::now().time_since_epoch().count();
        return seed;
    }
    static void hash_combine(size_t &seed, size_t v) {
        seed ^= v + 0x9e3779b97f4a7c15 + (seed<<6) + (seed>>2);
    }
    // ===== 기본 정수형 =====
    template<class T>
    typename enable_if<is_integral<T>::value, size_t>::type
    operator()(T v) const {
        return splitmix64((uint64_t)v + fixed_random());
    }
    // ===== 기타 기본 타입 =====
    template<class T>
    typename enable_if<!is_integral<T>::value, size_t>::type
    operator()(const T& v) const {
        return std::hash<T>()(v);
    }
    // ===== pair =====
    template<class A, class B>
    size_t operator()(const pair<A,B>& p) const {
        size_t seed = 0;
        hash_combine(seed, (*this)(p.first));
        hash_combine(seed, (*this)(p.second));
        return seed;
    }
    // ===== tuple =====
    template<class... Ts>
    size_t operator()(const tuple<Ts...>& t) const {
        size_t seed = 0;
        apply([&](const auto&... args) {
            (hash_combine(seed, (*this)(args)), ...);
        }, t);
        return seed;
    }
};

// pair 출력
template<class A, class B>
ostream& operator<<(ostream& os, const pair<A,B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

// 시퀀스 컨테이너: vector, list, deque
template<class C>
auto print_seq(ostream& os, const C& c) -> decltype(c.begin(), void()) {
    os << '{'; bool first=true;
    for (auto &x : c) { if(!first) os << ", "; first=false; os << x; }
    os << '}';
}
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { print_seq(os,v); return os; }
template<class T> ostream& operator<<(ostream& os, const list<T>& l) { print_seq(os,l); return os; }
template<class T> ostream& operator<<(ostream& os, const deque<T>& d) { print_seq(os,d); return os; }

// 셋 컨테이너: set, multiset, unordered_set
template<class C>
auto print_set(ostream& os, const C& c) -> decltype(c.begin(), void()) {
    vector<typename C::value_type> tmp(c.begin(), c.end());
    print_seq(os, tmp);
}
template<class T> ostream& operator<<(ostream& os, const set<T>& c) { print_set(os,c); return os; }
template<class T> ostream& operator<<(ostream& os, const multiset<T>& c) { print_set(os,c); return os; }
template<class T> ostream& operator<<(ostream& os, const unordered_set<T>& c) { print_set(os,c); return os; }


void init() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    init();



    return 0;
}