

세 가지 경우로 나눠볼 수 있다.

1. 1단계에서 필연적 `NO`에 도달하는 경우
2. 1단계는 통과했는데 그리디 알고리즘이 실패하는 경우
3. 1단계를 통과하고, 그리디 알고리즘도 성공한 경우





공식 해설을 인용해 본다. 

설명이 약간 부족하거나, 중의적이거나, 오류라고 생각되는 부분은 알아서 수정하며 직접 번역했다.

>Problem H: Scenery 
>
>Shortest judge solution: 1753 bytes.
>
>Shortest team solution (during contest): N/A bytes. 
>
>Python solutions by the judges: none 
>
>문제 H: Scenery
>
>가장 짧은 심사위원 답안: 1753 bytes.
>
>가장 짧은 팀 답안(대회 중): 정답자 없음
>
>파이썬을 이용한 심사위원 답안: 없음



>OK, this is the difficult problem of the set... This problem really tempts you to try some sort of a greedy solution. Let us see how that would go. Let us process time from the beginning. At any point in time, when we decide to take a photograph, we should – out of all the photographs we can currently take – choose the one for which the end time is the smallest (by a standard interchange argument). 
>
>좋아요, 이건 이번 대회의 전체 문제 중에서도 어려운 문제입니다. . 이 문제에서 여러분은 일종의 그리디 알고리즘을 사용하려는 유혹을 강하게 받았을 것입니다. 어떻게 될지 한번 해봅시다. 맨 처음부터 시간을 진행시킵니다. 어떤 시점에서 사진을 찍기로 결정했다면, 우리는 항상 촬영 시작이 가능한 사진들 중 __마감 시각(유효범위의 오른쪽 끝점)이 제일 이른 사진__을 선택해야 합니다. (일반적인 교환 논의에 의해)



>The tricky part is to choose whether you should actually start taking a photograph. Consider an input with two photographs to take. The first one will be available in the range [0, 5], the second in the range [1, 3], and the time to take a single photograph is 2. Then, at time zero, we will fail if we start to take the first photograph. On the other hand, if the second range was [2, 4], we would fail if we didn’t start a photograph at zero. So, some sort of smarts are going to be needed. 
>
>까다로운 부분은, 그 시점에서 실제로 사진을 찍을 건지 결정하는 일 자체입니다. 입력값으로 사진이 두 장만 들어왔다고 가정해보겠습니다. 첫번째는 [0, 5], 두번째는 [1, 3]의 유효 범위를 가지며 한 장을 찍는 데 걸리는 시간은 2입니다. 이 때 시각 0에서 첫번째 사진을 찍기 시작한다면 실패할 것입니다. 반면에 만약 두번째 사진의 유효범위가 [2, 4]였다면, 이번에는 시각 0에서 __찍기 시작하지 않으면 실패__할 것입니다. 어떤 묘책이 필요할 것 같군요.



>We will describe two solutions. The first, which we will describe in some detail, comes from the paper “Scheduling Unit-time Tasks With Arbitrary Release Times and Deadlines” by Garey, Johnson, Simons, and Tarjan (SICOMP, 1981). In that paper it is shown that the problem can even be solved in O(n log n), but we felt that getting a quadratic time solution was hard enough, and that is what we describe here.
>
>두가지 해법을 설명할 것입니다. 첫 번째 방법은 꽤 자세하게 설명할 건데, Garey, Johnson, Simons, Tarjan의 논문 `Scheduling Unit-time Tasks With Arbitrary Release Times and Deadlines(SICOMP, 1981)`에 바탕을 두고 있습니다. 그 논문에서는 이 문제가 심지어 O(n*log n)의 시간복잡도로 해결 가능함을 보이고 있습니다만, 우리는 O(n^2)의 해법도 충분히 어렵다고 느꼈기 때문에 이 방식으로 설명하겠습니다.



>We are going to adapt the naive solution above. Notice that in order to make the photograph with the range [1, 3] be even feasible, regardless of all the other photographs, we cannot start any photograph in the open range (−1, 1) – if we do, it will overlap the range [1, 3], and we will not be able to fit [1, 3] in. We will try to generalize that observation. 
>
>우리는 앞서 설명한 "우직한 접근법"을 채택하고자 합니다. [1, 3]의 유효범위를 갖는 사진을 확실하게 찍을 수 있으려면, 다른 사진들이 어떻든지 상관없이 개구간 (-1, 1)에서는 어떠한 사진도 찍기 시작할 수 없다는 점에 주목하십시오. 만약 그 구간에서 찍기 시작한다면 구간 [1, 3]과 겹치는데, [1, 3]의 촬영은 조정할 수 없기 때문입니다. 이러한 관찰 결과를 일반화하겠습니다.



>Take any interval [s,e], and consider all the photographs which become available no earlier than s, and become unavailable no later than e. Then, all these photographs have to fit into the interval [s,e]. We will now totally disregard their constraints (except that they have to be taken somewhere in [s,e]), and try to take them as late as possible. Note that since we disregard their constraints, they are all identical and we can just schedule them greedily. Let us look at the time C when we started taking the first (earliest) of those photographs. However we schedule these photographs in the interval, the first start time will not be later than C. If C < s, then we will simply not be able to take all the photographs. The interesting case is if C − s < t. Then, if any photograph gets started in the open interval (C − t,s), we will be unable to take all the photos from the interval [s,e], since we will not be able to take the first of them at C or before. 
>
>임의의 구간 [s, e]를 잡고, 유효범위가 이 구간 안에 속해 있는(개방시각은 s보다 빠르지 않고,  마감시각은 e보다 늦지 않은) 모든 사진을 생각해 봅시다. 그리고 그 사진들의 유효범위 제약조건을 전부(촬영이 [s, e] 내에서 이루어져야만 한다는 사실만 제외) 무시하고, 사진을 가능한 한 늦게 찍습니다. 제약조건을 무시했므로 그들은 내부적으로 모두 동일하면서, 우리는 "탐욕적으로" 스케줄을 만들 수 있습니다. 그 중 처음의 사진을 찍기 시작하는 시각을 C라고 하면, 사진들을 어떻게 재배치하더라도 그때의 "처음사진 촬영 시작 시각"은 C보다 나중일 수 없습니다. 만일 C < s 라면, 모든 사진을 찍는 것은 단순하게 불가능합니다. 재밌는 경우는 C - s < t 일 때인데, 만약 외부의 어떤 사진 촬영을 (C - t, s)에서 시작한다면, 아까의 [s, e] 구간 내의 사진들을 모두 촬영하는 것은 불가능해집니다. 왜냐하면 시각 C나 그 이전에 첫사진 촬영을 시작하는 것이 불가능해지니까요.



>This means we can mark the interval (C − t,s) as “forbidden”, and no photograph can ever be started then. We can also take any forbidden intervals we found so far into account when doing the greedy scheduling from the back (which might help us create more forbidden intervals). 
>
>따라서 우리는 (C - t, s)를 "금지구역"이라고 표시할 수 있습니다. 어떠한 사진도 금지구역에서 촬영을 시작할 수 없습니다. 또한 뒤에서부터 그리디 알고리즘을 적용 할 때, 그때까지 발견한 모든 금지구역을 계산에 넣을 수 있습니다. (그리디한 배치를 뒤부터 적용하는 이유는, 금지구역을 최대한 많이 만들기 위해서입니다.)

부연 설명: 여기서 "금지구역"이란 촬영을 __시작해서는 안 되는__ 구역임에 유의하자. 촬영시간의 뒷부분과 "금지구역"이 겹치는 것은 아무 문제가 되지 않는다.




>The full algorithm works as follows. We order all the availability times of all the photographs from latest to earliest. For each such time s, we iterate over all the end times e of the photographs, and for each interval [s,e] we run the algorithm above – take all the photographs that have to be taken fully within [s,e], ignore other constraints on them, assign times to them as late as possible (taking into account already created forbidden regions), and find the time C, which is the earliest possible start time of the first of those photographs. If C < s, return NO, and if C − s < t, produce a new forbidden region ending in s. 
>
>전체 알고리즘은 다음과 같은 흐름입니다. 모든 사진들의 유효범위를 허가시각(유효범위의 왼쪽 끝점) 역순으로 정렬합니다. 모든 허가시각 s에 대하여 모든 마감시각 e를 반복하여 돌며, 각각의 [s, e]에서 위의 알고리즘을 적용합니다. 즉,
>
>1. 유효범위가 [s, e]에 완전히 속하는 모든 사진들을 취한다.
>2. 제약 조건을 무시하고, 최대한 뒤로 사진들을 배치한다. 이 때 __기존에 생성된 금지구역을 고려한다.__
>3. C를 찾는다. C는 첫 사진을 촬영 시작할 수 있는 취후의 시각이다.
>4. C < s 면 `NO`를 return한다. C - s < t라면, 새로운 금지구역 (C- t, s)을 만들어낸다.

부연설명: 여기서 `latest`니 `earlist`이니 하는 말들은 허가시간을 기준으로 한 비교다.

>The above, implemented naively, is pretty slow. First, notice that while as written we can have a quadratic number of forbidden regions, it is trivial to collapse all the forbidden regions ending at any s into one (the one corresponding to the smallest C). Also, note that when we move from s to the previous s 0 , we don’t have to run the time assignment from scratch – we can just take the previous C value, and if the photograph starting at s 0 ends before some e, we just have to add one more photograph before the C (by default, at C − t, but possibly earlier if C − t is in a forbidden region). This allows us to progress through this stage in O(n 2 ) time. 
>
>위의 방식을 우직하게 구현한다면 꽤나 느리다. 
>
>먼저 이 사실에 주목해야 한다. 분명 금지구역의 갯수는 n^2에 비례하여 만들어지지만, 모든 s 각각에서, s를 오른쪽 끝점으로 같는 금지구역들은 쉽게 하나로 합쳐진다. (가장 작은 C를 가졌던 금지구역이 다 포함한다.) 또한 s에서 그 바로 앞의 s'으로 옮겨갈 때, 시간 할당을 처음부터 할 필요는 없다는 사실에 유의하라. 왜냐하면  s'가 허용시각인 사진이 시각 e나 e 이전에 마감되는 경우, s에서의 C를 취해 그 시각 왼쪽에 사진 1장의 촬영시간만 붙이면 되기 때문이다. (이렇게 C' = C - t가 되지만 만약 이렇게 만든 C'이 금지구역 안에 있다면 C'을 그 금지구역의 왼 끝점으로 재조정해야 한다.) 이러한 방식을 따르면 이 단계를 O(n^2)에 해결할 수 있다.



>Then, after this is done, we just run the standard “greedy” algorithm, taking the forbidden regions into account. The tricky part, of course, is to prove that this actually solves the problem. Obviously, if the greedy algorithm succeeds in taking the photographs, the answer is YES. Now, we will prove that if the greedy algorithm ends up taking a photograph after its end time, then we would have actually failed in the first phase. 
>
>이 단계가 완료된다면, 이제 금지구역을 고려해가며 일반적인 그리디 알고리즘을 적용하는 일만 남았다. 물론 까다로운 부분은 이 알고리즘이 실제로 문제를 해결할 수 있는지 증명하는 일이다. 그리디 알고리즘으로 사진을 제 시간에 모두 찍을 수 있다면 답은 당연히 `YES`다. (그럼 그리디 알고리즘이 실패하면 답이 `NO`라고 할 수 있을까? ) 우리는 다음을 증명할 것이다. "1단계를 통과한 그리디 알고리즘이 실패하는 경우는 없다. 그리디 알고리즘이 실패한다면, 1단계도 통과하지 못할 것이므로 "

부연설명: 여기서 "금지구역을 고려해가며 그리디 알고리즘을 적용"한다는 것은 다음의 의미다.

1. 이전 사진의 촬영이 끝나는 대로 다음을 무조건 시작하되, 여러개가 있다면 마감시간이 제일 이른 사진을 시작한다. (그 시각에서 촬영 가능한 사진이 없는 경우는 없다. 이유는 뒤에 나온다.)
2. 단 그 시각이 금지구역 내에 있다면, 그 금지구역의 오른 끝점으로 이동하여 촬영을 시작한다.



>
>Assume the greedy algorithm did take a photograph incorrectly. First, notice that if there are idle times (that is, times when no photograph is being taken by the greedy), we can assume they are all within forbidden regions. If there was an idle period without a forbidden region, let’s say at time X, it means that we have had no photograph available to take. So, all the photographs that were available before X got assigned and ended before X, and so they do not affect the photographs that become available after X. So, we can just remove these photographs from the set altogether and solve the smaller problem. 
>
>먼저 놀고있는 시간이 있다면(즉, 그리디 알고리즘에서 어떠한 사진도 찍히고 있지 않은 시간대) 그 시간은 반드시 금지구역에 속한다고 할 수 있는데, 이를 귀류법으로 증명하겠다. "놀고 있지만 금지구역이 아닌 어떤 시간대"를 X라고 부르자.  이는 그 시간대에는 남은 사진 중 찍을 수 있는 사진이 없음을 의미한다(그리디 알고리즘이므로 찍을 수 있는 사진이 있다면 찍고 있었을 것이다). 따라서 모든 사진은 X 이전에 배치가 완료되었거나, 허가시각이 X의 오른끝점 포함 이후인 사진으로 완전히 나뉘며, 전자는 후자에 전혀 영향을 미치지 않는다. 따라서 우리는 이 둘을 작은 문제 두 개로 분리할 수 있다. 따라서 그리디 알고리즘을 따랐을 때 어느 시간대에서 놀고 있다면, "금지구역이라서"라는 이유밖에는 없다.
>이제 1단계를 마친 그리디 알고리즘이 왜 실패할 수 없는지 귀류법으로 증명하겠다. 

부연설명: 여기서 "Assume the greedy algorithm did take a photograph incorrectly."라는 말은 이상하다.. 여기서 쓰이는 귀류법은 "1단계를 마친 후의 그리디 알고리즘이 실패할 수 없음"을 증명하지, "실패했는데 실제로는 가능한 경우는 없음"을 증명하는 것이 아니기 때문이다. 사실 포괄하는 말이기는 하지만...



>Now, assume the greedy algorithm failed. Take the first photograph Pi , with a deadline of ei , that got scheduled so it ends after ei . If no photograph that got scheduled earlier has a deadline later than ei , it means that the photographs up to Pi actually failed to fit into the range s0,ei – and so for that interval the first phase would’ve returned NO. If there is a photograph that has a deadline later than ei , let Pj be the latest of those photographs. Consider all the photographs Pk1 , . . . , Pkl that got scheduled between Pj and Pi , and let s be the earliest time at which any of those photographs (including Pj ) became available. Consider the first phase for the interval s,ei – it had to   have failed (because the greedy solution failed to put these photographs into this interval). 
>
>실패했다고 가정하자. 실패를 만들어내는 처음 사진 P[i]를 생각해보자. 그 사진은 마감시각은 e[i]인데 촬영이 e[i]가 넘어서야 끝났다.  
>
>1. 만약 이전에 찍은 사진들 중 마감시각이 e[i] 이후인 사진이 없다면: P[i]까지의 사진들을 [s[0], e[i]]에 우겨넣을 수 없음을 의미하게 된다(그리디가 아닌 어떠한 방법으로도!). 따라서 첫 단계에서 [s[0], e[i]]의 C를 구하는 과정에서 이미 `NO`를 반환했을 것이다.
>2. 만약 마감시각이 e[i] 이후인 사진이 이전 사진들 중 존재한다면: 그들 중 마지막사진을 P[j]라고 하자. P[j]와 P[i]의 사이에 있는 모든 사진들을 순서대로 P[k1], P[k2], ●●●  P[kl]라고 하자.a2p3g8oah;wegih

부연설명: 2의 설명이 완전히 잘못된 데다가 모호하기까지 해서 이해하느라 엄청 고생했다. 우선 s를 구하는데 저 __P[j]를 포함시키면 안 된다!!(excluding P[j]).__ 일단 [s[j+1], e[i]]의 C - t는 반드시 P[j]의 촬영시작 시각보다 왼쪽에 있다. 이 때 s[j+1]이 P[j] 촬영 시작 시각(을 포함)보다 왼쪽에 있었다면, P[j]가 가장 먼저 찍힐 리가 없다. 또 s[j+1]이 P[j]보다 크지만 C보다 오른쪽은 아니라면, 금지구역에 P[j]이 들어가는 셈이 되어 또 모순이다. 가능한 경우는 s[j]이 P[j], C 둘 다보다 큰 경우 뿐이며, 이건 1단계에서 `NO`를 반환한다.

 

>Thus, in all the cases where the greedy algorithm fails, the first phase had to have failed for some interval as well – so, if the first phase finished successfully, we are guaranteed the greedy algorithm will return a correct answer. 
>
>따라서, 그리디 알고리즘으로 배치에 실패하게 되는 모든 경우에, C와 금지구역을 만드는 첫번째 단계는 반드시 어떤 구간에서 이미 `NO`를 만들게 된다. (그러므로 모순이다. 그리디 알고리즘을 실행할 기회조차 주어지지 않으므로.)  따라서 첫번째 단계가 성공적으로 끝났다면, 그리디 알고리즘을 실행해보지 않아도, 성공할 것임이 저절로 보장된다.



>An alternative approach, which we will not prove, is an approach where we modify a naive branching approach. Naively, we can process forward through time, and maintain a set of possible states, where a possible state is the time when the photograph currently being taken (if any) ends, and the set of photographs that are available to take, but not yet started. This set of states is potentially exponential in size. We branch out (from all the states where there is no photograph being taken) when a new photograph becomes available, and we branch out when a photograph taking ends (to either not start a new photograph, or to start the one with the earliest deadline from those in the state). However, it is provable that we can actually have only one state where no photograph is being taken – when the algorithm ends up produces a new “nothing runs” state because some photograph just finished, one of the two states is strictly worse than the other. The proof, and the details of turning this into a quadratic algorithm, are left as an exercise to the reader.

부연설명: 또 다른 풀이는 생략한다.