import random
from map_data_types import *

def backtrack(map, colors, index):

    graph = map.graph
    N = len(graph)

    # print(index)

    if index == N:
        return True

    next_pt = graph[index]

    # Loop through all color combinations
    for next_color in colors:
        next_pt.color = next_color   # Set the color of this node

        # Check what the recursive call should do next
        if next_pt.has_conflicting_neighbors():
            continue
        else:
            if backtrack(map,colors,index + 1):
                return True
            else:
                continue
    next_pt.color = None
    return False

