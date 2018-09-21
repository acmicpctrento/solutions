#https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=532&problem=3794

import math
i = 1
sol = []
nball = 0
while(nball < 100000000002):
    nball = i*i
    n1 = (-1 + math.sqrt(1+4*((nball-1)*2)))/2
    if n1 % 1 == 0:
        sol.append(int(nball))
    i+=1

x = 1
y = 1
cont = 1
while x != 0 and y != 0:
    x, y = list(map(int, input().split()))
    res = 0
    if x != 0 or y != 0:
        for i in sol[1:]:
            if i > x and i < y:
                res+=1
        print("Case {}: {}".format(cont, res))
    cont+=1
