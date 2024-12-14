import numpy as np
import matplotlib.pyplot as plt

robots = [[tuple(int(''.join(filter(lambda s : s.isdigit() or s == '-', s1))) for s1 in lx.split(',')) for lx in l]
            for l in (x.split(' ') for x in open("input.txt").read().split('\n') if x)]

yrows = 103
xcols = 101

nslow = 0
nshigh = 1_000_000

def move_robot(pos, vel, time):
    return ( ( (pos[0] + (vel[0] * time)) % xcols ), ( (pos[1] + (vel[1] * time)) % yrows ) )

for time in range(nslow, nshigh + 1):
    grid = [[0 for __ in range(xcols)] for _ in range(yrows)]

    for i in range(len(robots)):
        final_pos = move_robot(robots[i][0], robots[i][1], time)
        grid[final_pos[1]][final_pos[0]] += 1 # grid[row_num][col_num]

    # hacky way to check grids which are mostly filled at the centre
    countfalse = 0
    for r in range(58, 62):
      for c in range(57, 62):
        if grid[r][c] == 0:
          countfalse += 1
      
    if countfalse <= 15:
      print('Seconds=', time)

      graph = np.array(grid)
      plt.imshow(graph, interpolation='none')
      plt.show()