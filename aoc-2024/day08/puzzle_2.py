INF_VAL = 99999

def calc_slope(t1, t2):
    den = (t2[0] - t1[0])
    return INF_VAL if den == 0 else ((t2[1] - t1[1]) / den)

map = [x for x in (open("input.txt", 'r').read().split('\n')) if x]
nrows = len(map)
ncols = len(map[0])

antennas = dict(list())
antinodes_set = set()

# get list of antennas
for i in range(nrows):
    for j in range(ncols):
        c = map[i][j]
        if c.isalnum():
            antennas.setdefault(c,[]).append((i, j))

# loop over pairs
for k,v in antennas.items():
    for i in range(len(v) - 1):
        for j in range(i+1, len(v)):
            slope = calc_slope(v[i], v[j])

            # for each pair loop over all points having same slope
            for m in range(nrows):
                for n in range(ncols):
                    p = (m,n)

                    if (p == v[i] or p == v[j]) or (calc_slope(p, v[i]) == slope):
                        antinodes_set.add(p)

print(len(antinodes_set))