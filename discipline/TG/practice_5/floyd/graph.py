#!/usr/bin/python

import copy

INF=999

def print_graph(graph, inf=INF):
    sz = len(graph)
    for i in range(1, sz):
        for j in range(1, sz):
            if (graph[i][j] != inf):
                print(graph[i][j], end=" ")
            else:
                print("INF", end=" ")
        print() 
    print()

# floyd algo implememtation
# return False if succeed
# return k value if found negative diagonal cost
def floyd(costs, paths, disabled_k=[], inf=INF):
    sz = len(costs)
    nodes_i = [i for i in range(1, sz)]
    nodes_j = [i for i in range(1, sz)]
    nodes_k = [i for i in range(1, sz) if i not in disabled_k]
    for k in nodes_k:
        for i in nodes_i:
            for j in nodes_j:
                if ((costs[i][k] < inf) and (costs[k][j] < inf)):
                    alter_cost = costs[i][k] + costs[k][j]
                    if (alter_cost < costs[i][j]):
                        costs[i][j] = alter_cost
                        paths[i][j] = k
                        if ((i == j) and (costs[i][j] < 0)):
                            print(i)
                            print_path(i, j, paths)
                            disabled_k.append(k)
                            return False
    return True

def print_path(i, j, paths):
    print(i, end="<-")
    c = paths[i][j]
    while (c != j):
        print(c, end="<-")
        c = paths[i][c]
    print(i, "<-", sep="")


# init_costs = [[0, -2, 3, -3],
#               [INF, 0, 2, INF],
#               [INF, INF, 0, -3],
#               [4, 5, 5, 0]]

# init_paths = [[0,0,0,0],
#               [1,1,1,1],
#               [2,2,2,2],
#               [3,3,3,3]]


init_costs = [[INF, INF, INF, INF, INF, INF],
              [INF, 0, 1, INF, INF, INF],
              [INF, INF, 0, 5, -5, INF],
              [INF, -7, -5, 0, INF, 6],
              [INF, -6, -5, 8, 0, 2],
              [INF, 3, 7, INF, INF, 0]]

init_paths = [[INF,INF,INF,INF,INF,INF],
              [INF,1,1,1,1,1],
              [INF,2,2,2,2,2],
              [INF,3,3,3,3,3],
              [INF,4,4,4,4,4],
              [INF,5,5,5,5,5]]

print("INIT COSTS")
print_graph(init_costs)

print("INIT PATHS")
print_graph(init_paths)

cur_costs = copy.deepcopy(init_costs)
cur_paths = copy.deepcopy(init_paths)
dis_k = [] # list of disabled k

while (not floyd(cur_costs, cur_paths, dis_k)):
    print_graph(cur_costs)
    print_graph(cur_paths)
    print(dis_k)
    cur_costs = copy.deepcopy(init_costs)
    cur_paths = copy.deepcopy(init_paths)
    

print("=== AFTER FLOYD ===")
print("COSTS:")
print_graph(cur_costs)
print("PATHS:")
print_graph(cur_paths)

# get_shortest_path(cur_paths, 2, 2, INF)
