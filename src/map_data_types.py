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
        self.triangles=None
        self.conflicts = 0