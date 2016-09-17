class Map():
    def __init__(self, graph):
        self.graph = graph
        self.num_colored = 0

    def clean_map(self):

        self.num_colored = 0

        for pt in self.graph:
            pt.color = None
            pt.conflicts = 0
            pt.color_reads = 0
            pt.color_writes = 0


class graph_edge():
    def __init__(self, ln, start_point, end_point, distance, if_checked=False):
        self.ln = ln
        self.start_point = start_point
        self.end_point = end_point
        self.distance = distance
        self.checked = if_checked
        self.theta = 0

class graph_point():
    def __init__(self, pt, color=None, poly=None):
        self.map = None
        self.pt = pt
        self.edges = []
        self.color = color
        self.conflicts = 0

        self.color_reads = 0
        self.color_writes = 0

        self.poly = poly
        self.all_edges = []
        self.triangles=None

        @property
        def color(self):
            self.color_reads = self.color_reads + 1
            return self.color

        @color.setter
        def color(self, value):
            self.color_writes = self.color_writes + 1

            if value == None:
                self.map.num_colored = self.map.num_colored - 1
            else:
                self.map.num_colored = self.map.num_colored + 1

            self.color = value

    # Returns true if any neighbors have conflicting colors
    def has_conflicting_neighbors(self):

        my_color = self.color

        if any(edge.end_point.color == my_color for edge in self.edges):
            return True
        else:
            return False



