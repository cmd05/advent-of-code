grid = [list(x) for x in open("input.txt").read().split('\n') if x]

nrows = len(grid)
ncols = len(grid[0])

area = 0
perimeter = 0
path = set()

def dfs(r, c, prev_col, new_col):
    global area, perimeter

    if r < 0 or r >= nrows or c < 0 or c >= ncols:
        perimeter += 1
        return
    
    if grid[r][c] != prev_col:
        if (r, c) not in path:
            perimeter += 1
        return
    
    grid[r][c] = new_col
    path.add((r, c))
    area += 1

    dfs(r, c + 1, prev_col, new_col)
    dfs(r, c - 1, prev_col, new_col)
    dfs(r + 1, c, prev_col, new_col)
    dfs(r - 1, c, prev_col, new_col)


def floodfill(r, c, new_col):
    global area, perimeter, path
    area = 0
    perimeter = 0
    path = set()
    
    prev_col = grid[r][c]
    if prev_col == new_col:
        return
    dfs(r, c, prev_col, new_col)


sym_filled = '1'
cum_price = 0

for i in range(nrows):
    for j in range(ncols):
        if grid[i][j].isalpha():
            floodfill(i, j, sym_filled)
            price = area * perimeter
            cum_price += price
            # print(area, perimeter, price) 

# print(grid)
print(cum_price)