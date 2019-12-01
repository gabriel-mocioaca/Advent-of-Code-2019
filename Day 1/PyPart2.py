inp = open("input.txt", "r")

vals = inp.readlines()

sum = 0

for x in vals:
    x = int(x)
    while x > 0:
        if x // 3 - 2 > 0:
            sum += x // 3 - 2
        x = x // 3 - 2

print(sum)