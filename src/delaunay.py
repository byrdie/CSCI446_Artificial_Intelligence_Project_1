from graphics import *
import random
import re

def calc_circle_center(pt1, pt2, pt3):
    x, y, z = complex(pt1.pt.getX(), pt1.pt.getY()), complex(pt2.pt.getX(), pt2.pt.getY()), complex(pt3.pt.getX(), pt3.pt.getY())
    w = z - x
    w /= y - x
    c = (x - y) * (w - abs(w) ** 2) / 2j / w.imag - x
    center = Point(-c.real, -c.imag)

    return center

def compute_poly(graph, win):
    print(len(graph))
    for j in range(0, len(graph)):

        pt1 = graph[j]
        poly_verts = []
        num_e = len(pt1.edges)
        for i in range(num_e):
            edge2 = pt1.edges[i]
            edge3 = pt1.edges[(i+1) % num_e]

            pt2 = edge2.end_point
            pt3 = edge3.end_point

            poly_vertex = calc_circle_center(pt1, pt2, pt3)
            poly_vertex.setFill("red")
            poly_vertex.draw(win)
            poly_verts.append(poly_vertex)

        colors = ['red', 'blue', 'green', 'purple', 'yellow', 'orange']
        next_poly = Polygon(poly_verts)
        next_poly.setOutline(colors[random.randint(0, len(colors) - 1)])
        next_poly.setWidth(1)
        next_poly.setFill(colors[random.randint(0, len(colors) - 1)])
        pt1.poly = next_poly
        next_poly.draw(win)