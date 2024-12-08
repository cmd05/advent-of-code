def in_bound(p, nx, ny):
    return p[0] >= 0 and p[0] < nx and p[1] >= 0 and p[1] < ny

map = [x for x in (open("input.txt", 'r').read().split('\n')) if x]
nrows = len(map)
ncols = len(map[0])

antennas = dict(list())

# get list of antennas
for i in range(nrows):
    for j in range(ncols):
        c = map[i][j]
        if c.isalnum():
            antennas.setdefault(c,[]).append((i, j))

antinodes_set = set()

for v in antennas.values():
    for i in range(len(v) - 1):
        for j in range(i+1, len(v)):
            p1 = (2 * v[i][0] - v[j][0], 2 * v[i][1] - v[j][1])
            p2 = (2 * v[j][0] - v[i][0], 2 * v[j][1] - v[i][1])

            if(in_bound(p1, nrows, ncols)):
                antinodes_set.add(p1)
            if(in_bound(p2, nrows, ncols)):
                antinodes_set.add(p2)

print(len(antinodes_set))