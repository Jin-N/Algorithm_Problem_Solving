#include <bits/stdc++.h>
using namespace std;
// 타입 단축
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
// 상수
const int INF = 1e9+7;
const ll LINF = 1e18;
// 전역 세팅
void init() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
int main() {
    init();

    int N, W;
    cin >> N >> W;

    vector<int> weights(N), values(N);
    for (int i = 0; i < N; i++){
        cin >> weights[i] >> values[i];
    }

    // 밀도(가치/부피)에 따라 내림차순으로 정렬된 번호 0~N-1 아이템들을 ordered에 저장한다.
    vector<int> ordered(N);
    iota(ordered.begin(), ordered.end(), 0);
    sort(ordered.begin(), ordered.end(), [&](int a, int b){
        return (long double)values[a]/weights[a] > (long double)values[b]/weights[b];
    });

    // V = 가능한 총 가치의 상한
    int V(0);
    ll cum(0);
    for (int i = -1; cum <= W;){
        i ++;
        V += values[ordered[i]];
        cum += weights[ordered[i]];
    }


    // 2차원 벡터 table 을 만든다. 내부 그룹은 서로 가치가 같다.
    // ordered를 훑으며 table 안에 담는다. table 내부의 각 그룹이 부피 오름차순으로 정렬되어있음은 자명
    // 이 때 각 그룹의 가치가 무엇인지 저장하는 groupValues를 만들어 같이 채워나간다. 
    // groupValues[i] = j 라면, table[i]에 속한 아이템들은 모두 가치가 j다.
    unordered_map<int, vector<ll>> mp;
    for (int id : ordered){
        mp[values[id]].push_back(weights[id]);
    }

    vector<int> groupValues;
    vector<vector<ll>> table;
    for (auto &p : mp){
        groupValues.push_back(p.first);
        table.push_back(p.second);
    }

    int G = groupValues.size();

    // cache는 각 단계에서 요구부피의 최소값을 저장하고, combi는 각 그룹에서 몇 개씩 아이템을 취해야 하는지 저장한다.
    vector<ll> cache(V+1, LINF);
    cache[0] = 0;
    vector<vector<int>> combi(V+1, vector<int>(G, 0));
    //무제한 배낭 문제처럼 cache를 채워나간다.
    for (int i = 0; i < V+1; i++){
        // 범위를 벗어나지 않도록 체크하는 거 잊지 말기.
        // 자신에게서 전파 가능한 다음 조합을 탐색한다.
        for (int j  = 0; j < G; j++){
            if (combi[i][j] == table[j].size()) continue; // 해당 그룹에서 더 이상 아이템 선택 불가
            if (cache[i] + table[j][combi[i][j]] > W) continue; // 배낭 용량 초과

            if (cache[i] + table[j][combi[i][j]] < cache[i + groupValues[j]]){
                cache[i + groupValues[j]] = cache[i] + table[j][combi[i][j]];
                // 해당 위치의 combi 정보를 갱신한다.
                combi[i + groupValues[j]] = combi[i];
                combi[i + groupValues[j]][j] += 1;
            }


        }
    }

    // cache가 유효한 값을 갖는 최대의 인덱스를 반환한다.
    int ans = 0;
    for (int i = 0; i <= V; i++) {
        if (cache[i] <= W) ans = i;
    }
    cout << ans <<"\n";
    return 0;
}