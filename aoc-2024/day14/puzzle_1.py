robots = [[tuple(int(''.join(filter(lambda s : s.isdigit() or s == '-', s1))) for s1 in lx.split(',')) for lx in l] 
            for l in (x.split(' ') for x in open("input.txt").read().split('\n') if x)]

yrows = 103
xcols = 101

nsecs = 100

def move_robot(pos, vel, time):
    return ( ( (pos[0] + (vel[0] * time)) % xcols ), ( (pos[1] + (vel[1] * time)) % yrows ) )

# I  |  II
# --------
# IV | III
quadcounts = [0 for _ in range(4)]

for i in range(len(robots)):
    final_pos = move_robot(robots[i][0], robots[i][1], nsecs)

    if (final_pos[0] < xcols // 2) and (final_pos[1] < yrows // 2): # first quadrant
        quadcounts[0] += 1
    elif (final_pos[0] > xcols // 2) and (final_pos[1] < yrows // 2): # second quadrant
        quadcounts[1] += 1
    elif (final_pos[0] > xcols // 2) and (final_pos[1] > yrows // 2): # third quadrant
        quadcounts[2] += 1
    elif (final_pos[0] < xcols // 2) and (final_pos[1] > yrows // 2): # fourth quadrant
        quadcounts[3] += 1

safety_factor = quadcounts[0] * quadcounts[1] * quadcounts[2] * quadcounts[3]

print(safety_factor)