from map_problem_gen import problem_gen, init_rand
from map_graphics import *
from backtrack import *
from map_data_types import *


# program entry point
if __name__ == '__main__':

    # Open graphics window
    win_sz = 1000
    win = open_win(win_sz)

    # Control initialization of PRNG for repeatibilty
    init_rand()

    colors = ["red","green","blue", "purple"]

    map = problem_gen(20, win_sz)

    map.clean_map()
    draw_graph(map.graph, win)

    print(backtrack(map, colors, 0,win))

    draw_poly(map.graph, win)


    write_win_to_eps(win, "test.eps")
    win.wait_window()




