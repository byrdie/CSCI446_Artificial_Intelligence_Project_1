import random
from map_data_types import *

def backtrack(map, colors, index, win):

    graph = map.graph
    N = len(graph)

    print(index)

    # Check if we've assigned all nodes
    if index == N:
        return True

    next_pt = graph[index]

    # Loop through all color combinations
    for next_color in colors:
        next_pt.color = next_color   # Set the color of this node

        poly = next_pt.poly
        poly.setFill(next_color)
        poly.draw(win)

        # Check what the recursive call should do next
        if next_pt.has_conflicting_neighbors():
            continue
        else:
            if backtrack(map,colors,index + 1, win):
                return True
            else:
                continue
    next_pt.color = None
    poly = next_pt.poly
    poly.setFill("yellow")
    poly.draw(win)
    return False


