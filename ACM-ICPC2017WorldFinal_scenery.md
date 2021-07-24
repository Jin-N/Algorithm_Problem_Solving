[문제링크](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV30Np8qABkBBAQU)

#### 서론

stains에 이은 두 번째 ACM-ICPC 도전이다.

저번에 stains 문제를 풀고 대회 문제에 흥미가 생겨서, 이번에는 내가 찾아서 시도해본 것인데 며칠씩이나 쓰고도 실패...

취업 준비를 하는 지금의 입장에서 이런 문제를 푸는 짓은 이번을 마지막으로 한동안 봉인해야 할 것 같다..

__이번 문제는 매우 어렵다!__ 2017년 당시 final 문제였는데 참가한 팀 중 단 한 팀도 맞추지 못한 유일한 문제다.

꽤 난해한 수학적 증명이 수반된 그리디 알고리즘을 사용하고 있어서, 해설을 이해하는 것만 해도 오래 걸렸다.

(물론 해설이 엉망인 탓도 있다. 맨 밑에 공식 해설을 번역&부연설명과 함께 달아놓았다.)



#### 문제 감상

이 문제의 인상깊은 점은, 원래 그리디 알고리즘이 타당하지 않은 문제인데 적절한 전처리를 거쳐 그리디 알고리즘을 써도 되는 문제로 바꾼다는 점이다. 그리고 그러한 전처리를 거친 문제에서 그리디 알고리즘이 타당함을 증명하는 과정은 매우 수학적이다. 예전에 직접 그리디 알고리즘의 타당성을 직접 증명해본 적이 딱 1번 있다. 내가 공부한 알고리즘 책 나와 있는 프림 알고리즘과 크루스칼 알고리즘의 타당성 증명이 부실해서 빠진 퍼즐조각을 직접 증명해본 것이었는데, 이 문제의 증명은 그것보다 몇 배는 더 어려운 것 같다.... 컴퓨터과학자들이 알고리즘을 만든다는 것이 어떠한 느낌의 일인지 대략적으로 감을 잡아볼 수 있는 좋은 경험이었다.

개괄적으로 말한다면, 이 "Yes or No" 문제는 전처리를 하는 1단계와 그리디 알고리즘을 적용하는 2단계로 나뉜다.

문제는 반드시 다음의 3가지 경우 중 하나로 나뉜다.

1. 1단계에서 필연적으로 `NO`에 도달하는 경우
2. 1단계는 통과했는데 그리디 알고리즘이 실패하는 경우
3. 1단계를 통과하고, 그리디 알고리즘도 성공한 경우

1번의 경우 답은 당연히 `NO`다. 3의 경우에는 당연히 `YES`다. 

해설은 여기서 __2번 케이스가 존재할 수 없음을 증명함으로써__, 1단계만 통과하면 나머지는 계산해보지 않아도 "YES"라고 말할 수 있음을 증명한다.



#### 개선점

- 1만X1만의 배열을 만드니 런타임 에러가 났으나, 길이 1만의 1차 배열만을 만들고 수정해가며 쓰느 방식을 택했더니 이제 더 이상 메모리 초과는 뜨지 않았다.

- 그 외 시도가능한 카드는 몇가지 더 있으나, 정답을 생각하지 않고 그 부분의 연산을 모조리 생략해도 여지없이 실행시간 초과가 뜬다. 단 1개의 큰 테스트케이스도 해결하지 못한다!! 해설과 같은 시간복잡도로 구현했는데도..... 시도 가능한 카드는 다음과 같다.
  - C가 들어갈 forbiddenArea를 이분탐색으로 찾는다.
  - pile_C 배열의 각 열을 개방시간 순이 아니라, 마감시간 순으로 정렬한다. 그러면 "한 지점에서 -t를 적용하게 된다면 오른쪽의 모든 열 또한 마찬가지다"라는 원리를 모든 행에서 적용할 수 있게 된다.



#### 훗날을 기약하며

- 인터넷에 올라온 정답 코드는 죄다 C++라 이해할 수가 없다. 나중에 C++을 공부하고 읽어보면 내가 무엇을 빠뜨렸는지 깨닫겠지..
- 아니면 나의 코드에는 아무 문제가 없는데 단지 python의 속도가 너무 느린 탓일 수도 있다!! 정보를 찾아보니 ACM-ICPC 심사위원들은 python을 허용하더라도, python으로 제한 시간 내에 풀 수 있는지 검증까지는 하지 않는다고 한다.. 뭐 이런;;;

#### 2021/07/24 마침내 풀었다.
- 해설이 아닌 논문까지 찾아 읽어서 시간복잡도를 O(nlogn)으로 개선했다. 논문을 이해하는 것 자체에 시간이 많이 들었고, 구현 후 디버깅에도 시간을 한참 쏟았다. 특히 레드블랙트리의 구현이 복잡했다 
- 무엇보다 swea 사이트 자체의 결함으로, import sys를 허용하지 않아서 재귀가 1000번 이상 호출되지 않도록 특이한 함수를 또 구현해야 했다.
- 문제에 착수한지 1년이 더 지나서 풀었다. 정말 대장정이었다. 노력을 쏟아부은 만큼 뿌듯하다!!




### 시도한 코드

```python
class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.parent = None
        self.key = key
 
    def get_follower(self):  # 오른쪽 서브트리가 없을 때 실행하면 에러남.
        cur = self.right
        while cur.left:
            cur = cur.left
        return cur
 
    def get_next(self):
        if self.right: return self.get_follower()
        cur = self
        while cur.parent and cur == cur.parent.right:
            cur = cur.parent
        return cur.parent
 
    def popfrom(self, tree):  # 루트노드 재설정 기능을 갖도록 하기 위해 tree를 매개변수로 받는다.
        if self.right and self.left:  # 차수 2
            follower = self.get_follower()
            follower.popfrom(tree)
            follower.left = self.left
            follower.right = self.right
            follower.left.parent = follower
            if follower.right:
                follower.right.parent = follower
        elif self.right:  # 차수 1
            follower = self.right
        elif self.left:  # 차수 1
            follower = self.left
        else:  # 차수 0
            follower = None
        # 위쪽과의 관계. 모든 경우에 해당
        if follower:  # 리프노드삭제가 아니었을 경우에만 추가실행
            follower.parent = self.parent
        if self == tree.root:  # cur가 루트노드였을 경우
            tree.root = follower
        else:  # cur가 루트노드가 아닐 경우
            if self.parent.key < self.key:
                self.parent.right = follower
            else:
                self.parent.left = follower
 
    def left_rotate(self):
        son = self.right
        parent = self.parent
        self.right = son.left  # 서브트리 떼주기
        if son.left:
            son.left.parent = self
        son.left = self  # 상하관계 재설정
        self.parent = son
        son.parent = parent  # 부모와의 관계
        if parent:
            if parent.key < self.key:
                parent.right = son
            else:
                parent.left = son
 
    def right_rotate(self):
        son = self.left
        parent = self.parent
        self.left = son.right  # 서브트리 떼주기
        if son.right:
            son.right.parent = self
        son.right = self  # 상하관계 재설정
        self.parent = son
        son.parent = parent  # 부모와의 관계
        if parent:
            if parent.key < self.key:
                parent.right = son
            else:
                parent.left = son
 
    def insert_rebalance(self):  # 자신은 확정적으로 red, 부모가 red일지도 모르는 상황에서 실행
        if not self.parent:  # 특이케이스. 루트노드일 경우 해당 노드의 색만 바꾸면 된다.
            self.isred = False
            return
        if not self.parent.isred: return  # 특이케이스2. 부모가 black이면 그대로 종료하면 된다.
        parent = self.parent
        grandpa = parent.parent
        if self.parent == grandpa.left:
            uncle = grandpa.right
        else:
            uncle = grandpa.left
        if uncle and uncle.isred:  # case1
            self.parent.isred = False
            uncle.isred = False
            grandpa.isred = True
            grandpa.insert_rebalance()
        elif self == parent.right and parent == grandpa.left:  # case2-1-1, 왼-오 꺾임
            parent.left_rotate()
            parent.insert_rebalance()
        elif self == parent.left and parent == grandpa.right:  # case2-1-2, 오-왼 꺾임
            parent.right_rotate()
            parent.insert_rebalance()
        else:  # case2-2, 쭉 뻗은 경우
            if self == parent.left:  # 좌로 뻗음
                grandpa.right_rotate()
            else:  # 우로 뻗음
                grandpa.left_rotate()
            grandpa.isred = True
            parent.isred = False
 
    def pop_rebalance(parent, x):
        # 특이한 점으로 문제지점의 부모가 메소드의 주체다. 따라서 문제지점이 root라면 재귀적 실행이 불가능함.
        # x의 형제는 None이 아님이 자명하다.
        # 기본형
 
        if x == parent.left:
            brother = parent.right
            if brother.isred:  # case 2-4
                parent.left_rotate()
                parent.isred, brother.isred = brother.isred, parent.isred
                parent.pop_rebalance(x)
                return
            elif brother.right and brother.right.isred:  # case *-2
                parent.left_rotate()
                parent.isred, brother.isred = brother.isred, parent.isred
                brother.right.isred = False
                return
            elif brother.left and brother.left.isred:  # case *-3
                brother.right_rotate()
                brother.isred = True
                brother.parent.isred = False
                parent.pop_rebalance(x)
                return
        # 대칭형
        else:
            brother = parent.left
            if brother.isred:  # case 2-4
                parent.right_rotate()
                parent.isred, brother.isred = brother.isred, parent.isred
                parent.pop_rebalance(x)
                return
            elif brother.left and brother.left.isred:  # case *-2
                parent.right_rotate()
                parent.isred, brother.isred = brother.isred, parent.isred
                brother.left.isred = False
                return
            elif brother.right and brother.right.isred:  # case *-3
                brother.left_rotate()
                brother.isred = True
                brother.parent.isred = False
                parent.pop_rebalance(x)
                return
                # case 1-1과 case 2-1만 남았다. 통합해서 시행한다.
        brother.isred = True
        if parent.isred:  # case 1-1
            parent.isred = False
        else:  # case 2-1
            if not parent.parent: return  # 루트노드라면 재귀실행이 필요없다.
            parent.parent.pop_rebalance(parent)
 
 
class BStree:
    def __init__(self):
        self.root = None
 
    def find(self, key):  # 못 찾으면 None 반환
        cur = self.root
        while cur:
            if cur.key < key:
                cur = cur.right
            elif key < cur.key:
                cur = cur.left
            else:
                break
        return cur
 
    def insert(self, node):
        cur = self.root
        while cur:  # cur가 node의 부모가 되는 지점까지 타고 내려가야 함.
            if cur.key < node.key:
                if cur.right:
                    cur = cur.right
                else:
                    cur.right = node
                    node.parent = cur
                    return
            elif node.key < cur.key:
                if cur.left:
                    cur = cur.left
                else:
                    cur.left = node
                    node.parent = cur
                    return
            else:
                return
        self.root = node  # 비어있는 트리였을 경우에만 위의 while문 대신 실행됨.
        return
 
    def pop(self, key):
        cur = self.find(key)
        if not cur:
            return
        cur.popfrom(self)
        return cur
 
    def find_smallest(self):
        cur = self.root
        if not cur: return
        while cur.left:
            cur = cur.left
        return cur
 
 
class RBtree(BStree):
    def insert(self, node):
        super().insert(node)
        node.isred = True
        node.insert_rebalance()  # 자신은 확정적으로 red, 부모가 red일지도 모르는 상황에서 리밸런스
        cur = self.root  # 로테이션으로 인해 루트가 바뀌었을 가능성이 있으므로 실행해야 한다.
        while cur.parent:
            cur = cur.parent
        self.root = cur
 
    def pop(self, key):
        cur = self.find(key)
        if not cur: return
        if cur.left and cur.right:
            follower = cur.get_follower()
            p_node = follower.right  # 문제가 될 노드를 마킹한다.
            if follower == cur.right:  # p_node가 None일 가능성이 있으므로 부모노드도 필요하다. p_parent도 None일 수 있음.
                p_parent = follower
            else:
                p_parent = follower.parent
        else:
            if cur.left:
                follower = cur.left
            else:
                follower = cur.right
            p_node = follower
            p_parent = cur.parent
 
        # 1. 후계자가 red이면 cur의 색깔로 바꿔주고 끝난다.
        if follower and follower.isred:
            follower.isred = cur.isred
            cur.popfrom(self)
            return cur
        # 이하 후계자가 blk임
        if not cur.left or not cur.right:
            cur.popfrom(self)
            if cur.isred:
                return cur
            else:  # 문제노드가 루트라면(부모가 없다면) 그냥 끝내고, 아니면 리밸런싱.
                if not p_parent:
                    return cur
 
        else:  # 쌍이었던 경우, 문제노드와 후계자 다름
            follower.isred = cur.isred
            cur.popfrom(self)
            if p_node and p_node.isred:  # 문제노드가 레드라면 색바꾸고 끝냄
                p_node.isred = False
                return cur
            else:
                pass
                # 문제노드가 루트일 가능성은 없음. 리밸런싱
 
        p_parent.pop_rebalance(p_node)
        ascender = self.root
        while ascender.parent:
            ascender = ascender.parent
        self.root = ascender
        return cur
 
####################### 여기서부터 본격적으로 시작 ##########################
# 4.에서 pseudo_offset들의 파편을 연산하기 위한 함수들. 여기에서는 find_set이 필요 없다.
def union_set(sup, inf):                
    parents[inf] = sup
    fragments[inf] -= fragments[sup]
def compress(index):                    # 반환하는 건 fragments 경로합(boss 제외). 경로압축 기능 포함
    if index == parents[index]: return 0
    fragments[index] += compress(parents[index])
    parents[index] = parents[parents[index]]
    return fragments[index]
def path_sum(index):                    # 경로압축 기능을 자연히 계승한다.
    return compress(index) + fragments[parents[index]]      # 두 항은 절대 순서 바꾸면 안 된다. compress연산이 뒤에 영향미침
def compress100(index, count):
    if index == parents[index]: return 0
    if count == 100: return fragments[index]
    fragments[index] += compress100(parents[index], count+1)
    parents[index] = parents[parents[index]]
    return fragments[index]
 
# 2.에서 유효한 대표 deadline을 찾기 위한 함수. 여기에서는 union_set이 필요 없다.
def find_set(index):
    if masters[index] != index:
        masters[index] = find_set(masters[index])
    return masters[index]
 
def get_pseudoC(index):
    load = 0
    cur = Deadlines.root
    while cur:
        load += cur.segment
        if deadlines[index] < cur.key:
            cur = cur.left
        elif cur.key < deadlines[index]:
            cur = cur.right
        else: break
    while parents[index] != parents[parents[index]]:
        compress100(index, 0)
    return deadlines[index] - load*t - path_sum(index)
# import sys
# sys.setrecursionlimit(1000000)
for test in range(1, int(input()) + 1):
    N, t = map(int, input().split())
    # 0. 준비작업. 정렬된 photos 배열, deadlines 배열(중복x), Deadlines 트리를 만든다. 
    # photos와 deadlines는 같이 만들어나간다.
    photos = []                                                                 
    for _ in range(N):
        photo = list(map(int, input().split()))
        photos.append(photo)
    photos.sort()
    photos_by_deadline = [ [time[0], time[1], i] for i, time in enumerate(photos) ]     # 임시로 필요한 배열
    photos_by_deadline.sort(key = lambda x: x[1])                                             # 각 photo의 세번째 요소는 개방시각 기준 순서를 나타낸다.
    deadline = float('inf')                                                     
    deadlines = []                                                              
    for photo in photos_by_deadline:
        if photo[1] != deadline:    
            deadline = photo[1]
            deadlines.append(deadline)
        photos[photo[2]].append(len(deadlines)-1)                                               # 각 photo에 마감시각(중복X) 기준 순서를 세번째 요소로 추가한다.
    del photos_by_deadline
    # task가 적재되는 Deadlines 트리 만들기. 적재 정보를 왜곡하므로 초기화 이후 노드 추가or삭제 금지.        
    Deadlines = RBtree()                
    for deadline in deadlines:
        node = Node(deadline)
        node.segment = 0
        Deadlines.insert(node)
    # pseudo critical time의 위상이 key인 트리 만들기. 각 위상 노드는 해당되는 deadline들의 boss의 index를 속성으로 갖는다. 
    fragments = [ 0 for _ in range(len(deadlines)) ]
    parents = [ i for i in range(len(deadlines)) ]
    PhaseC = RBtree()
    valid = len(deadlines)              # 유사편차가 어느 deadline부터 활성화되어있는지 나타내기 위한 변수
 
    rivals = [ i - 1 for i in range(len(deadlines)) ]       # 2에서 pseudoC 비교를 위한 바로 다음 유효대조후보의 인덱스를 저장하는 배열
    masters = [ i for i in range(len(deadlines)) ]          # 2에서 task의 deadline이 무효화된 것일 때, 대체시각을 찾기 위한 배열
    prime = photos[N-1][2]                                 # leastC를 갖는 deadline 번호
     
    for r in range(N - 1, -1, -1):      # 개방시각 release 역순으로 탐색. r은 task의 index, 즉 photos[r][0] 는 해당 개방시각이다.
        # 0. 유사편차가 활성화된 deadline 위치를 재조정한다.
        while valid != 0:
            if deadlines[valid-1] <= photos[r][0]: break
            valid -= 1
            phaseC = deadlines[valid]%t
            node = PhaseC.find(phaseC)
            if node:                                    # 이미 존재하는 위상이라면 합친다. 물론 신규는 경로합이 0이어야 한다.
                union_set(node.boss, valid)
            else:
                node = Node(phaseC)
                node.boss = valid
                PhaseC.insert(node)
     
        # 1. task를 Deadlines 트리에 적재한다.
        deadline = photos[r][1]
        cur = Deadlines.root
        while True:
            if cur.key < deadline:
                cur = cur.right
                continue
            cur.segment += 1
            if cur.left:                        # 왼쪽으로 가야되는 경우 + 해당 노드면서 리프노드가 아닌 경우
                cur.left.segment -= 1
                if cur.key != deadline:         #  왼쪽으로 가야 하는 경우
                    cur = cur.left
                    continue
            break                                 # 해당 노드면서 리프인 경우 + 해당노드면서 리프 아닌 경우가 합류한다. 
                 
        # 2. Deadlines 트리와 fragments 집합을 이용하여 pseudoC 계산, 무효화된 deadline들을 건너뛰도록 인접번호를 재조정
        challenger = find_set(photos[r][2])
        prime = min(challenger, prime)                      # 미답의 deadline에 처음으로 적재된 경우 prime을 조정해야 한다.
        pseudoC = get_pseudoC(challenger)
        while rivals[challenger] >= 0:           # 가로막힐 때까지 라이벌들을 꺾는다.
            if get_pseudoC(rivals[challenger]) < pseudoC: break
            masters[rivals[challenger]] = challenger
            rivals[challenger] = rivals[rivals[challenger]]
        if masters[prime] != prime:                             # prime이 challenger에 먹힌 경우 조정해야 한다.
            prime = challenger
        # 3. prime을 이용하여 leastC를 구한다. photos[r][0]을 넘어서면 실패. 아니면 forbidden region 생성
        leastC = get_pseudoC(prime)
        if leastC < photos[r][0]: break                  # halt
        if photos[r][0] + t <= leastC: continue       # 생성되는 금지구역 없음
        leftP = leastC%t        
        rightP = photos[r][0]%t
        # 4. forbidden region에 따라 pseudo_offset을 갱신한다.
        target = PhaseC.find(leftP)
        if leftP < rightP:               # a보다 크고 b보다 작은 모든 phaseC들을 a에 맞추어 통폐합
            if not target:                                  # 없을 경우 일단 새로 만들어본다.
                target = Node(leftP)
                PhaseC.insert(target)
                candidate = target.get_next()
                if candidate and candidate.key < rightP:     # 다음 녀석을 가로챈다.
                    target.boss = candidate.boss
                    fragments[candidate.boss] += candidate.key - leftP
                    PhaseC.pop(candidate.key)
                else:                                                       # 없어서 지우는 경우
                    PhaseC.pop(target.key)
                    continue
            while True:                                     # 공통적으로 실행
                candidate = target.get_next()
                if not candidate: break           # 더 이상 위상 후보가 없으면 종료
                if rightP <= candidate.key: break    # 끝점 범위를 벗어나면 종료
                union_set(target.boss, candidate.boss)
                fragments[candidate.boss] += candidate.key - leftP
                PhaseC.pop(candidate.key)                
        else:                             # a보다 크거나, b보다 작은 모든 phaseC들을 a에 맞추어 통폐합   
            if not target:                              # 없는 경우 일단 새로 만들어본다.
                target = Node(leftP)
                PhaseC.insert(target)
                candidate = target.get_next()
                if not candidate:
                    smallest = PhaseC.find_smallest()       # smallest는 절대 None이 아니다. target과 동일할 수는 있는데 어차피 다음에 걸러짐.
                    if smallest.key < rightP:
                        candidate = smallest
                if candidate:
                    target.boss = candidate.boss
                    fragments[candidate.boss] += (candidate.key - leftP)%t
                    PhaseC.pop(candidate.key)
                else:
                    PhaseC.pop(target.key)
                    continue
                                                     
            while True:                                 # 공통적으로 실행 ( leftP가 키인 phaseC가 있던 경우 + 없던 경우)
                candidate = target.get_next()
                if not candidate: break                         # 더 이상 위상 후보가 없으면 종료
                union_set(target.boss, candidate.boss)
                fragments[candidate.boss] += candidate.key - leftP
                PhaseC.pop(candidate.key)
            while True:
                candidate = PhaseC.find_smallest() 
                if not candidate.key < rightP: break     # 끝점 범위를 벗어나면 종료
                union_set(target.boss, candidate.boss)
                fragments[candidate.boss] += (candidate.key - leftP)%t
                PhaseC.pop(candidate.key)
 
    else:                                   # 스케줄링 성공 시 실행
        print('#{} yes'.format(test))
        continue
    print('#{} no'.format(test))
```

