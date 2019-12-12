inp = open("PyIn.txt", "r")
x = inp.read()

vals = x.split(sep=',')
vals = list(map(int, vals))

vals[1] = 12
vals[2] = 2

it = 0

while vals[it] != 99:
    if vals[it] == 1:
        vals[vals[it + 3]] = vals[vals[it + 1]] + vals[vals[it + 2]]
    elif vals[it] == 2:
        vals[vals[it + 3]] = vals[vals[it + 1]] * vals[vals[it + 2]]
    it += 4

print(vals[0])