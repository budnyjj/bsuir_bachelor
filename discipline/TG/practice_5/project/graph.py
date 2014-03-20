#!/usr/bin/python

import copy

def print_graph(graph):
    sz = len(graph)
    for i in range(sz):
        print(graph[i])
    print()

def floyd(costs, paths, inf):
    sz = len(costs)
    nodes = [i for i in range(sz)]
    for k in nodes:
        for i in nodes:
            for j in nodes:
                if ((costs[i][k] < inf) and (costs[k][j] < inf)):
                    alter_cost = costs[i][k] + costs[k][j]
                    if (alter_cost < costs[i][j]):
                        costs[i][j] = alter_cost
                        paths[i][j] = k
                        if ((i == j) and (costs[i][j] < 0)):
                            print(i)
                            print_graph(costs)
                            print_graph(paths)
                            print_path(i, j, paths)
                            return

def print_path(i, j, paths):
    print(i, end="<->")
    c = paths[i][j]
    while (c != j):
        print(c, end="<->")
        c = paths[i][c]
    print()



INF=999

# init_costs = [[0, -2, 3, -3],
#               [INF, 0, 2, INF],
#               [INF, INF, 0, -3],
#               [4, 5, 5, 0]]

# init_paths = [[0,0,0,0],
#               [1,1,1,1],
#               [2,2,2,2],
#               [3,3,3,3]]


init_costs = [[0, 1, INF, INF, INF],
              [INF, 0, 5, -5, INF],
              [-7, -5, 0, INF, 6],
              [-6, -5, 8, 0, 2],
              [3, 7, INF, INF, 0]]

init_paths = [[0,0,0,0,0],
              [1,1,1,1,1],
              [2,2,2,2,2],
              [3,3,3,3,3],
              [4,4,4,4,4]]

print("INIT COSTS")
print_graph(init_costs)

print("INIT PATHS")
print_graph(init_paths)

cur_costs = copy.deepcopy(init_costs)
cur_paths = copy.deepcopy(init_paths)

floyd(cur_costs, cur_paths, INF)

print("=== AFTER FLOYD ===")
print("COSTS:")
print_graph(cur_costs)
print("PATHS:")
print_graph(cur_paths)

# get_shortest_path(cur_paths, 2, 2, INF)
