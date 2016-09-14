from graphics import *

def open_win(win_sz):
    win = GraphWin('Graph Coloring', win_sz, win_sz)
    win.setBackground('white')
    return win

def write_win_to_eps(win, filename):
    win.postscript(file=filename, colormode='color')

def draw_graph(graph, win):

    for pt in graph:
        circ = Circle(pt.pt, 4)
        circ.setFill("black")
        circ.draw(win)
        for edge in pt.edges:
            edge.ln.draw(win)

def draw_poly(graph, win):

    for pt in graph:
        poly = pt.poly
        poly.setFill(pt.color)
        poly.draw(win)

