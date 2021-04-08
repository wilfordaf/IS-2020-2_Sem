def FindLis(A, B):
    matrix = [[0] * (len(B) + 1) for _ in range(len(A) + 1)]
    for i in range(1, len(A) + 1):
        for j in range(1, len(B) + 1):
            if A[i - 1] == B[j - 1]:
                matrix[i][j] = matrix[i - 1][j - 1] + 1
            else:
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1])

    ans = ""
    i = len(A)
    j = len(B)
    while i > 0 and j > 0:
        if A[i - 1] == B[j - 1]:
            ans += A[i - 1]
            i -= 1
            j -= 1
        elif matrix[i - 1][j] == matrix[i][j]:
            i -= 1
        else:
            j -= 1
    return ans[::-1]


str1 = str(input())
str2 = str(input())
print(FindLis(str1, str2))

