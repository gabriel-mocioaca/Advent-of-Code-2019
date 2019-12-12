inp = open("input.txt", "r")

vals = inp.readlines()

sum = 0

for x in vals:
    sum += int(x) // 3 - 2

print(sum)