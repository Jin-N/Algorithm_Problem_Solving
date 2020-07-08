'''문제링크 https://programmers.co.kr/learn/courses/30/lessons/42840'''

def solution(answers):
    L = len(answers)
    pattern1 = [1, 2, 3, 4, 5]*(L//5 + 1)
    pattern2 = [2, 1, 2, 3, 2, 4, 2, 5]*(L//8 + 1)
    pattern3 = [3, 3, 1, 1, 2, 2, 4, 4, 5, 5]*(L//10 + 1)
    score = [0]*4
    for i in range(L):
        if answers[i] == pattern1[i]: score[1] += 1
        if answers[i] == pattern2[i]: score[2] += 1
        if answers[i] == pattern3[i]: score[3] += 1
            
    MAX = max(score)
    return sorted([ i for i in range(1, 4) if score[i] == MAX ])
