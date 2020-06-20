def solution(lines):
    '''
    '각 시각에서 이후 1초 동안'이 아닌 각 시각에서의 처리량만 검사하는 문제로 바꾼다면,
    각 로그의 시작 시각을 1초씩 앞으로 연장시켜야 한다.
    '''
    refine = [ line.split()[1:]  for line in lines ] # 각 요소는 [끝나는 시각, 시간] 이다.
    start_times = []
    finish_times = []
    for info in refine:
        temp = info[0].split(':')
        finish = 3600*int(temp[0]) + 60*int(temp[1]) + float(temp[2])
        start = finish - 1 - float(info[1].rstrip('s')) + 0.001 
        start_times.append(start)
        finish_times.append(finish)
    
    start_times.sort()
    finish_times.sort()
    sIndex = 0          # 시작시각을 담은 리스트의 탐색자  
    fIndex = 0          # 종료시각을 담은 리스트의 탐색자
    traffic = 0
    ans = 0
    while sIndex < len(start_times):
        if start_times[sIndex] < finish_times[fIndex]:
            traffic += 1
            if traffic > ans: ans = traffic
            sIndex += 1
        else:
            traffic -= 1
            fIndex += 1
    return ans
