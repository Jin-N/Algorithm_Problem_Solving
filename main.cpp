#include <bits/stdc++.h>
#include <atcoder/maxflow>
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
    int N, A, B;
    cin >> N >> A >> B;
    vector<string> S(N);
    rep(i, 0, N)
        cin >> S[i];
    // A, B의 소인수분해 결과 2의 지수가 동일하면 1, 다르면 0 
    int GCD = gcd(A, B);
    const bool type = (A/GCD % 2) && (B/GCD % 2); 

    int source = N*N, sink = N*N + 1;
    //S[i][j]의 위치의 노드번호는 i*N + j
    atcoder::mf_graph<int> g(N*N + 2);
    vector<int> dx = {A, A, B, B};
    vector<int> dy = {B, -B, A, -A};
    
    // coloring.즉 각 정점이 source, sink 중 어디와 연결되는지 결정, isBlack은 1이면 검은칸, 0이면 흰칸, -1이면 막힌 칸
    vector<int> isBlack(N*N, -1);
    rep(i, 0, N)
        rep(j, 0, N){
            if(S[i][j] == '#') continue;
            if(type){
                if(i/GCD % 2){   //줄무늬로 color가 바뀐다.
                    g.add_edge(source, i*N+j, 1);
                    isBlack[i*N+j] = 1;
                }
                else{
                    g.add_edge(i*N+j, sink, 1);
                    isBlack[i*N+j] = 0;
                }
            }
            else{
                if((i/GCD % 2) ^ (j/GCD % 2)){   //격자무늬로 color가 바뀐다.
                    g.add_edge(source, i*N+j, 1);
                    isBlack[i*N+j] = 1;
                }
                else{
                    g.add_edge(i*N+j, sink, 1);
                    isBlack[i*N+j] = 0;
                }                     
            }
        }

    // 그룹 간 간선 생성. 동시에 adj 작성
    vector<vector<int>> adj(N*N);
    rep(i, 0, N)
        rep(j, 0, N){
            if(S[i][j] == '#') continue;
            rep(k, 0, 4){
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx >= N || ny >= N || ny < 0 || S[nx][ny] == '#') continue;
                int pos = i*N+j;
                int nPos = nx*N+ny;
                if(isBlack[pos]){
                    g.add_edge(pos, nPos, 1);
                }
                else{
                    g.add_edge(nPos, pos, 1);
                }
                adj[pos].push_back(nPos);
                adj[nPos].push_back(pos);
            }
        }

    g.flow(source, sink);

    vector<bool> isSside = g.min_cut(N*N);
    vector<string> ans = S;
    rep(i, 0, N){
        rep(j, 0, N){
            int pos = i*N + j;
            if( (isBlack[pos] == 1 && isSside[pos]) || (isBlack[pos] == 0 && !isSside[pos]))
                ans[i][j] = 'o';
        }
    }
    rep(i, 0, N)
        cout << ans[i] << endl;

    return 0;
}