from map_problem_gen import problem_gen, init_rand
from map_graphics import *
from map_data_types import *


# program entry point
if __name__ == '__main__':

    # Open graphics window
    win_sz = 1000
    win = open_win(win_sz)

    # Control initialization of PRNG for repeatibilty
    init_rand()

    graph = problem_gen(10, win_sz)

    draw_poly(graph, win)
    draw_graph(graph, win)

    write_win_to_eps(win, "test.eps")
    win.wait_window()




