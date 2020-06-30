'''문제 링크
https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWcPjEuKAFgDFAU4&categoryId=AWcPjEuKAFgDFAU4&categoryType=CODE'''

for test in range(1, int(input())+1):
    N = int(input())
    temp = list(map(int, input().split()))
    arr = set()
    for i in range(len(temp)):
        for j in range(i+1, len(temp)):
            arr.add(temp[i]*temp[j])

    ans = -1
    for num in arr:
        temp = str(num)
        for d in range(len(temp) - 1):
            if temp[d] > temp[d+1]: break
        else:
            ans = max(ans, num)

    print('#{} {}'.format(test, ans))
