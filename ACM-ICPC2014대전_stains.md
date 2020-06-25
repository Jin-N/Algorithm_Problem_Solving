[문제링크](https://swexpertacademy.com/main/code/contestProblem/contestProblemDetail.do?contestProbId=AV6XmNZ6AXEDFAXy&categoryId=AV6XmNZ6AXEDFAXy&categoryType=CODE)

장장 3일이 걸린 문제. 고생한 만큼 기록도 상세하게 남기고 싶다.

결국 해설을 보고 풀었지만 내공을 다질 수 있었던 문제였다.



#### 핵심 흐름

처음에는 가지치기 트리 문제로 접근했다. `wash` 재귀함수로 구현.

1. 유의미한 청소도구 사용을 찾아내어, 그 청소도구가 지우는 얼룩들의 묶음을 노드로 삼는다.
2. 매 노드마다 포함할 건지 안할 건지를 선택하여 2방향으로 분기한다.
3. 만약 그 노드만이 지울 수 있는 얼룩이 있다면, 그 노드는 반드시 포함한다(가지치기)
4. "선택된 노드들이 지우는 모든 얼룩"이 전체 얼룩과 같아진다면 종료한다.



#### 추가 아이디어

가지치기가 들어있으므로 나름 합리적이라고 생각했다. 그러나 무자비한 런타임 에러

연산을 줄이기 위해 다음과 같은 아이디어를 추가했었다.

- 누군가의 하위호환이 되는 노드는 제외한다. 즉 어떤 노드가 13번, 32번 2개의 얼룩을 지우는데, 다른 노드는 13번 얼룩 1개만 지울 수 있다면, 후자의 노드는 버려도 무방하다. ( 아래의 코드에는 구현되어있지 않음)
- 얼룩들의 조합을 비트마스킹한다. 이렇게 하면 2차 배열을 1차배열로 간단하게 만들 수 있어 메모리가 절약되고, 비트연산자를 쓰면 속도도 빨라진다.
- 얼룩들을 그룹화하였다. 서로 다른 그룹에 있는 얼룩은 절대 하나의 청소도구로 같이 닦일 수 없다. 그러면 전체의 해는 각 그룹의 해를 더한 것과 같으므로, 문제를 각개격파 할 수 있고, 연산량을 대폭으로 줄일 수 있다. (전체 문제를 비슷한 크기의 그룹 2개로 쪼개면 대략 2^(2n)에서 2^(n+1)로 연산량이 줄어든다.) 



마지막 아이디어를 적용할 때에는 집합 처리 알고리즘을 이용했다. 나름 어려웠던 부분이었기에 이것이 바로 문제의 핵심이라고 생각했으나 결과는 역시 __런타임 에러__..



### 시간초과 되었던 코드

```python
def wash(idx, Sum):  # idx번째 이후의 청소도구만 사용할 수 있다. Sum은 지금까지 청소한 얼룩의 비트 정보
    if Sum + 1== 1<<width: return 0  # 기저조건
 
    is_unique = False  # 이 청소도구가 아니면 지울 수 없는 얼룩이 있는지 검사
    nexts = 0
    for cleaner in checklist[idx+1:]:
        nexts |= cleaner
    if checklist[idx] & ~Sum & ~nexts:
        is_unique = True
 
    ans = wash(idx + 1, Sum|checklist[idx]) + 1
    if not is_unique:  # unique하지 않다면, 해당 청소도구를 쓰지 않는 선택지도 가능함
        ans = min(ans, wash(idx + 1, Sum))
 
    return ans
 
 
def findSet(x):
    if x != parents[x]:
        parents[x] = findSet(parents[x])
    return parents[x]
 
 
for test in range(1, int(input()) + 1):
    R, C = map(int, input().split())  # 의미 없는 정보
    N = int(input())
    stainsAll = []
    for _ in range(N):
        stainsAll.append(tuple(map(int, input().split())))
    stainsAll.sort(key=lambda x: x[1])  # 연산을 절약하기 위함.
 
    parents = [i for i in range(N)]
    for idx, stain in enumerate(stainsAll):
        for idx2, comparator in enumerate(stainsAll):
            if idx2 <= idx: continue
            if comparator[1] > stain[1] + 2: break
            if abs(comparator[0] - stain[0]) > 2: continue
 
            if findSet(idx) > findSet(idx2):
                parents[findSet(idx2)] = findSet(idx)
            else:
                parents[findSet(idx)] = findSet(idx2)
 
    roots = [x for x in range(N) if findSet(x) == x]
    groups = [[] for _ in range(len(roots))]
    for idx, stain in enumerate(stainsAll):
        groups[roots.index(findSet(idx))].append(stain)
 
    answer = 0
    for stains in groups:  # stains.sort(key=lambda x: x[1]) 는 불필요. 이미 정렬되어 있다. 왼쪽의 얼룩부터 지워나간다.
        x = stains[0][1]
        col = stains[-1][1] - x + 1
        arr = [ [-1]*(col+2) for _ in range(R+2) ]
        for i, stain in enumerate(stains):
            arr[stain[0]-1][stain[1]-x] = i
 
        width = i+1
        checklist = []
        for j in range(col):
            for i in range(R):
                if arr[i+2][j] == -1 and arr[i+1][j] == -1 and arr[i][j] == -1: continue
                if arr[i][j] == -1 and arr[i][j+1] == -1 and arr[i][j+2] == -1: continue
                temp = 0
                for a in range(3):
                    for b in range(3):
                        if arr[i+a][j+b] != -1:
                            temp |= (1<<arr[i+a][j+b])
                checklist.append(temp)
 
        answer += wash(0, 0)
 
    print('#{} {}'.format(test, answer))
```



#### 남는 카드는 DP밖에 없었다.

그런데 최적부분구조를 어떻게 잡아야 하고, 그들간의 관계를 점화식으로 어떻게 표현할 지 알아내는 것이 매우 까다로웠다.

문제가 1차원이었다면 간단하다. 

- idx에서 얼룩이 없다면: D[idx] == D[idx-1]
- idx에서 얼룩이 있다면: D[idx] == D[idx-3] + 1

그런데 2차원으로 확장하면 문제가 복잡해진다.

idx열에서 얼룩이 존재한다면, D[idx]는 D[idx-3]에서 청소도구를 몇개 더 써야 할까?

- 최소: idx열의 얼룩을 닦는 데 필요한 갯수
- 최대: idx-2, idx-1, idx열의 얼룩을 닦는 데 필요한 갯수

idx-3까지 쓴 청소 도구가 idx-2, idx-1 열의 얼룩을 __일부만__ 지워주기 때문에 정확한 식을 세우기가 어렵다.



#### 문제의 힌트

결국 해설을 보고서야 알아냈지만, 최적부분구조를 정수가 아닌 2차원 배열로 만들어서 __인근 열에서 사용한 청소도구들의 정보를 담는 것__이 해법이었다. 사실 문제에서 이미 힌트가 있었다. 

- 전체 좌표의 높이가 최대 10이어서, 각 열에서 청소도구들을 조합할 수 있는 경우의 수는 상당히 작다. (29) 
- 청소도구가 닦는 범위가 3X3에 불과하여, 담아야 하는 인근 열의 조합이 작다. (만약 청소도구가 100X100이었다면 99차원의 배열을 만들어야 DP로 풀 수 있을 것이다.)



#### 추가 아이디어

통과 후에도 실행시간을 단축시키기 위해 추가로 다음의 알고리즘을 적용하였다.

- 다음 열이 완전히 비어있다면 `sol[j+1][later][cur]` 에서 later가 0인 경우(다음 열에서 아무 청소도구도 배치하지 않음)만 계산한다. 0이 아닌 경우는 반드시 비효율적이므로 생각할 필요가 없다. 

- 효율적인 조합만 `economic`에 담아서, `later`는 반드시 이 안에서만 돌도록 한다. 여기서 __효율적__이라 함은, 해당 조합을 구성하는 어떠한 청소도구도 낭비되지(아무 얼룩도 못 지우지) 않는다는 뜻이다. 코드로 구현하기가 의외로 까다로운 부분이었는데, 2차원 배열 `components`를 만드는 것으로 해결했다.



__두번째 아이디어는 실행시간을 오히려 늘려버렸다.__ 아무래도 효율적인 효율적인 조합을 찾는 과정 자체가 무거웠던 같다.



#### 후기

해설을 본 다음에도, 버그를 찾아내기까지 시간이 좀 걸렸다. 바로 런타임 에러 때문인데...

#### [] 를 () 로 잘못 썼는데, 런타임에러(memory 초과)가 뜬다!

 파이참에서 돌려보고 나서야 "리스트는 callable하지 않다"라는 메세지를 보고 알 수 있었다.



### 정답

```python
num = [ 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4 ]
pattern = [0, 7, 14, 28, 56, 112, 224, 448, 896, 63, 119, 126, 231, 238, 252, 455, 462, 476, 504, 903, 910, 924, 952, 1008, 1022, 1015, 959, 511, 1023]
components = [ 
    [], [7], [14], [28], [56], [112], [224], [448], [896], 	
    [56, 7], [112, 7], [112, 14], [224, 7], [224, 14], [224, 28], [448, 7], [448, 14], [448, 28], [448, 56], [896, 7], [896, 14], [896, 28], [896, 56], [896, 112], 
    [896, 112, 14], [896, 112, 7], [896, 56, 7], [448, 56, 7],
]

INF = float('inf')
for test in range(1, int(input())+1):
    R, C = map(int, input().split())
    N = int(input())
    band = [0]*(C+1)
    for _ in range(N):
        r, c = map(int, input().split())
        band[c] |= 1<<(r-1)

    # sol[j][cur][prev]는 j열의 패턴이 cur이고, j-1열의 패턴이 prev인 경우에 한해서, j열까지 다 닦기 위해 써야 하는 청소도구의 최소갯수.
    sol = [ [ [INF]*29 for cur in range(29)  ]   for j in range(C+1) ]	#값이 -1이면 불가능하거나, 고려할 필요가 없는 경우의 수
    sol[0][0][0] = 0
    for j in range(0, C):
        if band[j+1] == 0:				# 다음 열이 비었다면 빠른 연산이 가능하다.
            for cur in range(29):
                sol[j+1][0][cur] = min([ sol[j][cur][prev] for prev in range(29) ])
            continue
            
        economic = []					# 다음 열의 패턴 중 비효율적인 것은 모두 버린다.
        for later in range(28):
            for component in components[later]:
                if not band[j+1] & component: break
            else:
                economic.append(later)
        if len(economic) == 28:
            economic.append(28)
            
        for cur in range(29):
            for prev in range(29):
                if sol[j][cur][prev] == INF: continue
                # to_wash = band[j+1] & ~(pattern[cur] | pattern[prev])
                for later in economic:
                    if band[j+1] & ~(pattern[cur] | pattern[prev] | pattern[later]): continue
                    sol[j+1][later][cur] = min(sol[j+1][later][cur], sol[j][cur][prev] + num[later])

    print('#{} {}'.format(test, min([sol[C][i][j] for i in range(29) for j in range(29) ])))
```

