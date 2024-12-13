from itertools import groupby
from operator import itemgetter

grid = [list(x) for x in open("input.txt").read().split('\n') if x]

nrows = len(grid)
ncols = len(grid[0])

area = 0
perimeter = 0
path = set()
borders = set()

def dfs(r, c, prev_col, new_col, dir):
    global area, perimeter

    if r < 0 or r >= nrows or c < 0 or c >= ncols:
        # perimeter += 1
        borders.add((r, c, dir))
        return
    
    if grid[r][c] != prev_col:
        if (r, c) not in path:
            # perimeter += 1
            borders.add((r, c, dir))
        return
    
    grid[r][c] = new_col
    path.add((r, c))
    area += 1

    dfs(r, c + 1, prev_col, new_col, 'R')
    dfs(r, c - 1, prev_col, new_col, 'L')
    dfs(r + 1, c, prev_col, new_col, 'U')
    dfs(r - 1, c, prev_col, new_col, 'D')


def floodfill(r, c, new_col):
    global area, perimeter, path, borders
    area = 0
    perimeter = 0
    path = set()
    borders = set()
    
    prev_col = grid[r][c]
    if prev_col == new_col:
        return
    dfs(r, c, prev_col, new_col, 'N')

def nsides(l):
    sides = 0
    l.sort()

    for k, g in groupby(enumerate(l), lambda ix : ix[0] - ix[1]):
        # print(list(map(itemgetter(1), g)))
        sides += 1

    return sides

def calc_sides():
    cum_sides = 0

    # loop over columns including ends
    for i in range(-1,  ncols + 1):
        l1 = [x for x in borders if x[1] == i and x[2] == 'L']
        rvals1 = [x[0] for x in l1]
        nsides1 = nsides(rvals1)
        cum_sides += nsides1
        if(nsides1): print('col', i, 'L: rvals1', rvals1, 'nsides', nsides1)


        l2 = [x for x in borders if x[1] == i and x[2] == 'R']
        rvals2 = [x[0] for x in l2]
        nsides2 = nsides(rvals2)
        cum_sides += nsides2
        if(nsides2): print('col', i, 'R: rvals2', rvals2, 'nsides', nsides2)

    # loop over rows including ends
    for i in range(-1,  nrows + 1):
        l1 = [x for x in borders if x[0] == i and x[2] == 'U']
        cvals1 = [x[1] for x in l1]
        nsides1 = nsides(cvals1)
        cum_sides += nsides1
        if(nsides1): print('row', i, 'U: cvals1', cvals1, 'nsides', nsides1)


        l2 = [x for x in borders if x[0] == i and x[2] == 'D']
        cvals2 = [x[1] for x in l2]
        nsides2 = nsides(cvals2)
        cum_sides += nsides2
        if(nsides2): print('row', i, 'D: cvals2', cvals2, 'nsides', nsides2)

    return cum_sides

sym_filled = '1'
cum_price = 0

for i in range(nrows):
    for j in range(ncols):
        if grid[i][j].isalpha():
            floodfill(i, j, sym_filled)
            sides = calc_sides()
            price = area * sides
            cum_price += price
            print('price', price)
            print('---')
            # num_sides = calc_sides()
            # price = area * num_sides
            # cum_price += price
            # print(area, perimeter, price) 

# print(grid)
print('cum price', cum_price)