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
    def __init__(self, ln, start_point, end_point, distance, if_checked=False):
        self.ln = ln
        self.start_point = start_point
        self.end_point = end_point
        self.distance = distance
        self.checked = if_checked
        self.theta = 0

# Definition of 2D cross product

class graph_point():
    def __init__(self, pt, color=None, poly=None):
        self.pt = pt
        self.edges = []
        self.color = color
        self.poly=poly

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

        # If the two lines are the same, we say that they do not cross
        if(p0_x == p2_x and p0_y == p2_y and p1_x == p3_x and p1_y == p3_y):
            return False

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

    except ZeroDivisionError:   # If the two lines
        return False

# Compute the Euclidian distance of a line segment
def distance(line1):
    x_dist = line1.getP2().getX() - line1.getP1().getX()
    y_dist = line1.getP2().getY() - line1.getP1().getY()

    return math.sqrt(x_dist * x_dist + y_dist * y_dist)


def elim_crossings(N, win, fullcon_graph, graph, all_edges):

    # Implement graph constructing algorithm defined in problem statement
    escape = True
    vertex_escape = [False] * N  # All elements must be true to escape loop
    while (escape):
        i = random.randint(0, N - 1)  # Select random point
        edges = fullcon_graph[i].edges  # Select all edges from random point
        num_edges = len(edges)

        # Find next closest point
        for j in range(0, num_edges):

            test_edge = edges[j]

            if test_edge.checked == False:  # Proceed only if we haven't checked this edge
                test_edge.checked = True  # Make sure to inform the program we checked the edge

                # test_edge.ln.draw(win)

                # Check that the test edge does not cross any current edges
                if len(all_edges) == 0:
                    graph[i].edges.append(test_edge)
                    all_edges.append(test_edge)
                    # test_edge.ln.setFill('green')
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
                        graph[i].edges.append(test_edge)
                        all_edges.append(test_edge)
                        #test_edge.ln.setFill('green')
                        test_edge.ln.draw(win)
                        break
                        # else:
                        #     test_edge.ln.undraw()

            # Escape based on full trips through all FOR loops
            if j == num_edges - 1:
                vertex_escape[i] = True

        if all(item == True for item in vertex_escape):
            escape = False

def set_point(x_pt, y_pt):
    next_pt = Point(x_pt, y_pt)
    next_pt.setFill('white')
    next_pt.draw(win)

    # Store two copies of the list for determining crossings
    # And another two copies for determining polygons
    next_full_graph_pt = graph_point(next_pt)
    next_graph_pt = graph_point(next_pt)
    next_full_polygraph_pt = graph_point(next_pt)
    next_polygraph_pt = graph_point(next_pt)

    fullcon_graph.append(next_full_graph_pt)
    graph.append(next_graph_pt)
    fullcon_polygraph.append(next_full_polygraph_pt)
    polygraph.append(next_polygraph_pt)

def draw_graph(graph, win):

    for pt in graph:
        for edge in pt.edges:
            edge.ln.draw(win)

def main():

    set_point(0,0)
    set_point(0, win_sz-1)
    set_point(win_sz-1,0)
    set_point(win_sz-1,win_sz-1)

    # Fill the list of points
    for i in range(0,N-4):
        x_pt = random.randint(0,win_sz-1)
        y_pt = random.randint(0,win_sz-1)
        set_point(x_pt, y_pt)

    # Create list of all edges between vertices and store in list
    for i in range(0, N):
        edges = []  # Save all edges from each vertex for storage in list
        for j in range(0, N):
            if j != i:
                ln = Line(fullcon_graph[i].pt, fullcon_graph[j].pt)
                ln.setFill('black')
                ln.setWidth(3)
                edge = graph_edge(ln, fullcon_graph[i], fullcon_graph[j], distance(ln))
                edges.append(edge)

        edges.sort(key=lambda x: x.distance)
        fullcon_graph[i].edges = edges

    # Eliminate all crossings in main graph
    elim_crossings(N, win, fullcon_graph, graph, all_edges)

    # Now to construct a possible polygon structure that represents this graph
    # Start by finding the midpoint of all edges
    for edge in all_edges:
        mid_pt = edge.ln.getCenter()
        mid_pt.setFill('red')
        mid_pt.draw(win)

        mid_pt_obj = graph_point(mid_pt)
        mid_pts.append(mid_pt_obj)

    # Now connect all original points to every possible midpoint
    for i in range(0,N):
        edges = []

        if i >= 0 and i <= 3:
            ln = Line(fullcon_polygraph[i].pt, fullcon_polygraph[i].pt)
            ln.setFill('red')
            edge = graph_edge(ln, fullcon_polygraph[i], fullcon_polygraph[i], distance(ln))
            edges.append(edge)
        for j in range(0,len(mid_pts)):
            ln = Line(fullcon_polygraph[i].pt, mid_pts[j].pt)
            ln.setFill('red')
            edge = graph_edge(ln, fullcon_polygraph[i], mid_pts[j], distance(ln))
            edges.append(edge)

        edges.sort(key=lambda x: x.distance)
        fullcon_polygraph[i].edges=edges

    # As before, eliminate all crossings with polygraph
    elim_crossings(N, win, fullcon_polygraph, polygraph, all_edges)

    # Plug results into graph object

    # for i in range(0,N):
    #     poly_verts = []
    #
    #     colors=['red','blue','green','purple', 'yellow', 'orange']
    #
    #     # Sort edges by angle
    #     for j in range(0, len(polygraph[i].edges)):
    #         dx = polygraph[i].edges[j].end_point.pt.getX() - polygraph[i].edges[j].start_point.pt.getX()
    #         dy = polygraph[i].edges[j].end_point.pt.getY() - polygraph[i].edges[j].start_point.pt.getY()
    #         polygraph[i].edges[j].theta = math.atan2(dy,dx)
    #         if(i==1 and j==0):
    #             polygraph[i].edges[j].theta = 2 * math.pi
    #         print(polygraph[i].edges[j].theta)
    #     polygraph[i].edges.sort(key=lambda x: x.theta)

        # Calculate polygons
        # for j in range(0, len(polygraph[i].edges)):
        #     next_vert = polygraph[i].edges[j].end_point.pt
        #     poly_verts.append(next_vert)
        #
        #
        # next_poly = Polygon(poly_verts)
        # next_poly.setOutline('white')
        # next_poly.setWidth(2)
        # next_poly.setFill(colors[random.randint(0, len(colors) - 1)])
        # graph[i].poly = next_poly
        # next_poly.draw(win)

        # draw_graph(graph,win)
        # draw_graph(graph, win2)


    win.postscript(file="/home/byrdie/School/CSCI446_Artifical_Intelligence/CSCI446_Artificial_Intelligence_Project_1/src/test.eps", colormode='color')
    win.wait_window()
    win2.wait_window()


# Open graphics window
win_sz = 1000
win = GraphWin('Graph Coloring', win_sz, win_sz)
win.setBackground('white')

# win2 = GraphWin('Graph Coloring Poly', win_sz, win_sz)
# win2.setBackground('white')

N = 10  # Number of points provided by command line (not yet)
fullcon_graph = []  # List of vertices of the graph
graph = []
all_edges = []

fullcon_polygraph = []
polygraph = []
mid_pts = []
all_poly_edges = []

init_rand()
main()

