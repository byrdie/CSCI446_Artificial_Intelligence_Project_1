from graphics import *
import random
import math
import os
import time

def init_rand(seed=None):
    if seed is None:
        try:
            seed = os.urandom(8)
        except NotImplementedError:
            seed = time.time()
    print('seed: %s' % seed)
    random.seed(seed)

class graph_edge():
    def __init__(self, ln, distance, if_checked):
        self.ln = ln
        self.distance = distance
        self.checked = if_checked

# Definition of 2D cross product


# Check if lines cross by checking if both x and y coordinates simultaneously switch order
# Solution given by http://stackoverflow.com/a/1968345
def does_cross(line1, line2):

    try:
        p0_x = line1.getP1().getX()
        p0_y = line1.getP1().getY()
        p1_x = line1.getP2().getX()
        p1_y = line1.getP2().getY()
        p2_x = line2.getP1().getX()
        p2_y = line2.getP1().getY()
        p3_x = line2.getP2().getX()
        p3_y = line2.getP2().getY()

        if(p0_x == p2_x and p0_y == p2_y and p1_x == p3_x and p1_y == p3_y):
            return True

        s1_x = p1_x - p0_x
        s1_y = p1_y - p0_y
        s2_x = p3_x - p2_x
        s2_y = p3_y - p2_y

        s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y)
        t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y)

        i_x = p0_x + (t * s1_x)
        i_y = p0_y + (t * s1_y)


        if (s >= 0 and s <= 1 and t >= 0 and t <= 1):
            if ((i_x == p0_x and i_y == p0_y) or (i_x == p1_x and i_y == p1_y) or (i_x == p2_x and i_y == p2_y) or (i_x == p3_x and i_y == p3_y)):
                return False
            else:
                return True
        else:
            return False

    except ZeroDivisionError:   #If the two lines are the same, we say that they do not cross
        return False

# Compute the Euclidian distance of a line segment
def distance(line1):
    x_dist = line1.getP2().getX() - line1.getP1().getX()
    y_dist = line1.getP2().getY() - line1.getP1().getY()

    return math.sqrt(x_dist * x_dist + y_dist * y_dist)



def main():

    # Open graphics window
    win_sz = 1000
    win = GraphWin('Graph Coloring', win_sz, win_sz)
    win.setBackground('black')


    N = 100     # Number of points provided by command line (not yet)
    vertices = []    # List of vertices of the graph
    fullcon_graph = {}      # Dictionary of vertices and all possible edges
    graph = {}
    all_edges = []      #

    # Fill the list of points
    for i in range(0,N):
        x_pt = random.randint(0,win_sz-1)
        y_pt = random.randint(0,win_sz-1)
        next_pt = Point(x_pt, y_pt)
        next_pt.setFill('white')
        next_pt.setOutline('white')
        next_pt.draw(win)
        vertices.append(next_pt)

    # Create list of all edges between vertices and store in dictionary
    for i in range(0,N):
        edges = []  # Save all edges from each vertex for storage in dictionary
        for j in range(0,N):
            if j != i:
                ln = Line(vertices[i], vertices[j])
                ln.setFill('red')
                edge = graph_edge(ln, distance(ln), False)
                edges.append(edge)

        edges.sort(key=lambda x: x.distance)
        fullcon_graph[vertices[i]] = edges      # Insert into dictionary

    # Implement graph constructing algorithm defined in problem statement
    escape = True
    vertex_escape = [False] * N     # All elements must be true to escape loop
    while(escape):
        i = random.randint(0,N-1) # Select random point
        edges = fullcon_graph[vertices[i]]      # Select all edges from random point
        num_edges = len(edges)

        # Find next closest point
        for j in range(0, num_edges):

            test_edge = edges[j]



            if test_edge.checked == False:  # Proceed only if we haven't checked this edge
                test_edge.checked = True  # Make sure to inform the program we checked the edge

                # test_edge.ln.draw(win)

                # Check that the test edge does not cross any current edges
                if len(all_edges) == 0:
                    graph[vertices[i]] = test_edge
                    all_edges.append(test_edge)
                    test_edge.ln.setFill('green')
                    test_edge.ln.draw(win)
                    break
                else:
                    crosses = False
                    for edge in all_edges:

                        # edge.ln.setFill('yellow')
                        # edge.ln.draw(win)

                        if does_cross(test_edge.ln, edge.ln):
                            crosses = True

                        # edge.ln.setFill('green')
                        # edge.ln.draw(win)

                    if crosses == False:
                        graph[vertices[i]] = test_edge
                        test_edge.ln.setFill('green')
                        test_edge.ln.draw(win)
                        all_edges.append(test_edge)
                        break
                    # else:
                    #     test_edge.ln.undraw()


            # Escape based on full trips through all FOR loops
            if j == num_edges - 1:
                vertex_escape[i] = True

        if all(item == True for item in vertex_escape):
            escape = False

    win.wait_window()


init_rand(b'\xcd\r\x0e\x95x\x9ab\xa6')
main()

