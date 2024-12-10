map = [x for x in open("input.txt", 'r').read().split('\n') if x]
nrows = len(map)
ncols = len(map[0])

def is_next(a, b):
    return ord(b) - ord(a) == 1

path = set()
rating = 0

def dfs(r, c, peak, last_point, is_first):
    global path
    global rating

    if last_point == peak:
        return True
    
    if (r < 0 or r >= nrows or
        c < 0 or c >= ncols or
        (not is_first and not is_next(map[last_point[0]][last_point[1]], map[r][c])) or
        (r, c) in path):
        return False
    
    path.add((r, c))

    if is_first:
        is_first = False
    
    res = (dfs(r, c + 1, peak, (r, c), is_first) or
           dfs(r, c - 1, peak, (r, c), is_first) or
           dfs(r + 1, c, peak, (r, c), is_first) or
           dfs(r - 1, c, peak, (r, c), is_first))

    if res:
        rating += 1

    path.remove((r, c))
    
    if(len(path) == 0):
        return res

peaks = []

# find all peaks
for i in range(nrows):
    for j in range(ncols):
        if map[i][j] == '9':
            peaks.append((i, j))

cum = 0

# go through all '0' points
for i in range(nrows):
    for j in range(ncols):
        if map[i][j] == '0':
            rating = 0

            # go through all peaks
            for peak in peaks:
                path = set()
                dfs(i, j, peak, (i, j), True)

            # print("rating", rating)
            cum += rating

print('cum rating:', cum)