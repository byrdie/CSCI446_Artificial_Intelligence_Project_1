import random
from map_data_types import *

def backtrack(map, k, index):

    graph = map.graph
    N = len(graph)

    # print(index)

    if index == N:
        return True

    next_pt = graph[index]

    # Loop through all color combinations
    for j in range(1, k+1):
        next_pt.color = Color(j)   # Set the color of this node

        # Check what the recursive call should do next
        if next_pt.has_conflicting_neighbors():
            continue
        else:
            if backtrack(map,k,index + 1):
                return True
            else:
                continue
    next_pt.color = None
    return False


def looping_backtrack(map, colors):
    graph = map.graph
    N = len(graph)
    k = len(colors)

    solutions = [None] * N
    i = 0
    j = 0
    while True:

         next_pt = graph[i]


