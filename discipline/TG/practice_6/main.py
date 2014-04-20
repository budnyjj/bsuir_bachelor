import itertools as it

INF = 999
NUM_NODES = 8

def calc_sum(perm, vertex):
    s = 0
    for i in range(1, len(perm)):
        s += vertex[perm[i-1]][perm[i]]
    s += vertex[perm[-1]][perm[0]]
    return s
    
    


vertex = [[INF, INF, 9, 5, 10, 6, 11, 4],
          [INF, INF, INF, INF, 11, 4, 9 ,4],
          [9, INF, INF, 4, INF, INF, 2, INF],
          [5, INF, 4, INF, INF, 11, 9, INF],
          [10, 11, INF, INF, INF, 12, INF, INF],
          [6, 4, INF, 11, 12, INF, INF, INF],
          [11, 9, 2, 9, INF, INF, INF, INF],
          [4, 4, INF, INF, INF, INF, INF, INF]]


nodes = tuple(node for node in range(NUM_NODES))

opt_sum = INF
opt_perm = ()


for perm in it.permutations(nodes):
    perm_sum = calc_sum(perm, vertex)
    if opt_sum > perm_sum:
        print(perm)
        print(perm_sum)
        print()
        opt_sum = perm_sum
        opt_perm = perm

