l = 153517
r = 630395

def check(x):
    s = str(x)
    for i in range(1, len(s)):
        if s[i] < s[i - 1]:
            return False
    cnt = 1
    for i in range(1, len(s)):
        if s[i] == s[i - 1]:
            cnt += 1
        elif cnt == 2:
            return True
        else:
            cnt = 1
    if cnt == 2:
            return True
    return False

cnt = 0
for i in range(l, r + 1):
    if check(i) is True:
        cnt += 1

print(cnt)