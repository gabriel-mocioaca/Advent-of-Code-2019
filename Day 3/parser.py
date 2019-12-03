inp = open("in.txt", "r")
x = inp.readlines()

out = open("input.txt", "w")

vals = x[0].split(',')
out.write(str(len(vals)) + '\n')
for it in vals:
    out.write(it[0] + ' ' + it[1:] + '\n')

vals = x[1].split(',')
out.write(str(len(vals))  + '\n')
for it in vals:
    out.write(it[0] + ' ' + it[1:] + '\n')

x = [[False for i in range(2500)] for j in range(2500)]