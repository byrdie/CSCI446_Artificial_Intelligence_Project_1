from map_problem_gen import problem_gen, init_rand
from backtrack import *
from map_data_types import *
from genetic import *


# program entry point
if __name__ == '__main__':

    # Open graphics window
    win_sz = 1000
    win = GraphWin('Graph Coloring', win_sz, win_sz)
    win.setBackground('white')

    # Control initialization of PRNG for repeatibilty
    #init_rand(b'\xa3\xf3\x11"\xab\xf3\xf4\xf1')
    init_rand()
    colors = ["red","green","blue", "purple"]

    map = problem_gen(70, win_sz)

    map.clean_map()

    #print(backtrack(map, colors, 0))
    genetic = GeneticAlgorithm(map, 4)

    map = genetic.run()
    map.draw_poly(win)
    map.draw_graph(win)

    win.postscript(file="test.eps", colormode='color')
    win.wait_window()



# Test branching
