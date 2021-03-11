a = [8, 5, 0, 1, 2, 100, -1, 0]

tmp = 0
cnt = 1
length = len(a)

for i in range(length):
    while True:
        if cnt == length:
            break
        if a[i] > a[cnt]:
            tmp = a[i]
            a[i] = a[cnt]
            a[cnt] = tmp
        cnt += 1
    cnt = i + 1

print(a)
