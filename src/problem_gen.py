from graphics import *
import random
import math
import os
import time
from delaunay import compute_poly

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
        self.all_edges = []
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


def elim_crossings(N, win, graph, all_edges):

    # Implement graph constructing algorithm defined in problem statement
    escape = True
    vertex_escape = [False] * N  # All elements must be true to escape loop
    while (escape):
        i = random.randint(0, N - 1)  # Select random point
        edges = graph[i].all_edges  # Select all edges from random point
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
                    # test_edge.ln.draw(win)
                    break
                else:
                    crosses = False
                    for edge in all_edges:

                        # edge.ln.setFill('yellow')
                        # edge.ln.draw(win)

                        if does_cross(test_edge.ln, edge.ln):
                            crosses = True
                            break

                        # edge.ln.setFill('green')
                        # edge.ln.draw(win)

                    if crosses == False:
                        graph[i].edges.append(test_edge)
                        all_edges.append(test_edge)
                        # test_edge.ln.setFill('green')
                        # test_edge.ln.draw(win)
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

def centroid(pts):

    X = 0
    Y = 0
    for pt in pts:
        X = X + pt.pt.getX()
        Y = Y + pt.pt.getY()

    X = math.floor(X / len(pts))
    Y = math.floor(Y / len(pts))
    center_pt = Point(X,Y)
    center_pt.setFill('red')
    # center_pt.draw(win)

    return graph_point(center_pt)

def main():

    set_point(0,0)
    set_point(0, win_sz-1)
    set_point(win_sz-1,0)
    set_point(win_sz-1,win_sz-1)

    # Fill the list of points
    for i in range(0,N-4):
        x_pt = random.randint(10,win_sz-10)
        y_pt = random.randint(10,win_sz-10)
        set_point(x_pt, y_pt)

    # Create list of all edges between vertices and store in list
    for i in range(0, N):
        edges = []  # Save all edges from each vertex for storage in list
        for j in range(0, N):
            if j != i:
                ln = Line(graph[i].pt, graph[j].pt)
                ln.setFill('black')
                ln.setWidth(1)
                edge = graph_edge(ln, graph[i], graph[j], distance(ln))
                edges.append(edge)

        edges.sort(key=lambda x: x.distance)
        graph[i].all_edges = edges

    # Eliminate all crossings in main graph
    elim_crossings(N, win, graph, all_edges)

    # Sort edges by angle
    for i in range(0,N):
        for j in range(0, len(graph[i].edges)):
            dx = graph[i].edges[j].end_point.pt.getX() - graph[i].edges[j].start_point.pt.getX()
            dy = graph[i].edges[j].end_point.pt.getY() - graph[i].edges[j].start_point.pt.getY()
            graph[i].edges[j].theta = math.atan2(dy, dx)
            if (i == 1 and j == 0):  # 4th quadrant needs special treatment
                graph[i].edges[j].theta = 2 * math.pi
        graph[i].edges.sort(key=lambda x: x.theta)
    #
    # # Compute polygon representation
    # compute_poly(graph, win)
    # draw_graph(graph, win)
    # Now to construct a possible polygon structure that represents this graph


    # Group triangles into list
    triangles = []
    centers = []
    for j in range(4, len(graph)):

        pt1 = graph[j]
        num_e = len(pt1.edges)
        for i in range(num_e):
            edge2 = pt1.edges[i]
            edge3 = pt1.edges[(i+1) % num_e]

            pt2 = edge2.end_point
            pt3 = edge3.end_point
            triangles.append([pt1, pt2, pt3])

    # Find the center of each triangle
    for triangle in triangles:
        circ1 = Circle(triangle[0].pt,4)
        circ1.setFill("blue")
        circ1.draw(win)
        circ2 = Circle(triangle[1].pt,4)
        circ2.setFill("blue")
        circ2.draw(win)
        circ3 = Circle(triangle[2].pt,4)
        circ3.setFill("blue")
        circ3.draw(win)
        new_center = centroid(triangle)
        circ4 = Circle(new_center.pt,4)
        circ4.setFill("blue")
        circ4.draw(win)
        new_center.pt.draw(win)
        if all( ((center.pt.getX() != new_center.pt.getX()) or (center.pt.getY() != new_center.pt.getY())) for center in centers):
            centers.append(new_center)
        else:
            print("rejected triangle")
            # new_center.pt.setFill("black")
            # new_center.pt.draw(win)
        circ1.undraw()
        circ2.undraw()
        circ3.undraw()
        circ4.undraw()

    # Draw line from each point to centers of triangle
    for i in range(0,N):
        edges = []
        pt1 = polygraph[i]
        for pt2 in centers:
            ln = Line(pt1.pt, pt2.pt)
            ln.setFill('red')
            # ln.draw(win)
            edge = graph_edge(ln, pt1, pt2, distance(ln))
            edges.append(edge)

        edges.sort(key=lambda x: x.distance)
        polygraph[i].all_edges = edges

    elim_crossings(N, win, polygraph, all_edges)



    # Now connect all midpoints to polygraph
    for i in range(0,N):
        pt = graph[i]

        # If we're in a corner, we need to point to ourself
        if i >= 0 and i <= 3:
            ln = Line(pt.pt, pt.pt)
            new_edge = graph_edge(ln, pt, pt, distance(ln))
            polygraph[i].edges.insert(0,new_edge)

        for edge in pt.edges:
            mid_pt = edge.ln.getCenter()
            mid_pt_obj = graph_point(mid_pt)
            ln = Line(pt.pt, mid_pt)
            new_edge = graph_edge(ln, pt, mid_pt_obj, distance(ln))
            polygraph[i].edges.append(new_edge)

    # Plug results into graph object
    for i in range(0,N):
        poly_verts = []

        colors=['red','blue','green','purple', 'yellow', 'orange']

        # Sort edges by angle
        for j in range(0, len(polygraph[i].edges)):
            dx = polygraph[i].edges[j].end_point.pt.getX() - polygraph[i].edges[j].start_point.pt.getX()
            dy = polygraph[i].edges[j].end_point.pt.getY() - polygraph[i].edges[j].start_point.pt.getY()
            polygraph[i].edges[j].theta = math.atan2(dy,dx)
            if(i==1 and j==0):      # 4th quadrant needs special treatment
                polygraph[i].edges[j].theta = 2 * math.pi
        polygraph[i].edges.sort(key=lambda x: x.theta)

        # Calculate polygons
        for j in range(0, len(polygraph[i].edges)):
            next_vert = polygraph[i].edges[j].end_point.pt
            poly_verts.append(next_vert)


        next_poly = Polygon(poly_verts)
        next_poly.setOutline('white')
        next_poly.setWidth(1)
        next_poly.setFill(colors[random.randint(0, len(colors) - 1)])
        graph[i].poly = next_poly
        next_poly.draw(win)

    draw_graph(graph, win)


    win.postscript(file="/home/byrdie/School/CSCI446_Artifical_Intelligence/CSCI446_Artificial_Intelligence_Project_1/src/test.eps", colormode='color')
    win.wait_window()

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
full_mid_pts=[]
mid_pts = []
all_poly_edges = []

init_rand()
main()
