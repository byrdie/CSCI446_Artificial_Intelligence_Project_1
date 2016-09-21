from map_problem_gen import problem_gen, init_rand
from backtrack import *
from map_data_types import *
import time
import cProfile

# program entry point
if __name__ == '__main__':

    # Open graphics window
    win_sz = 1000
    win = GraphWin('Graph Coloring', win_sz, win_sz)
    win.setBackground('white')

    # Control initialization of PRNG for repeatibilty
    init_rand()

    colors = ["red","green","blue", "purple"]

    # pr = cProfile.Profile()
    # pr.enable()
    map = problem_gen(50, win_sz)
    # pr.disable()
    print("generated map")

    map.clean_map()

    start_time = time.time()
    backtrack(map, 4, 0)
    end_time = time.time()

    [reads, writes] = map.count_reads_writes()
    print("Reads: ", reads)
    print("Reads/s" ,  reads / (end_time - start_time))
    print("Writes: ", writes)
    print("Writes/s" ,  writes / (end_time - start_time))

    map.draw_poly(win)
    map.draw_graph(win)

    # pr.print_stats(sort="calls")

    win.postscript(file="test.eps", colormode='color')
    win.wait_window()




# Test branching
