disk_map = open("input.txt").readlines()[0].rstrip('\n')
id_map = []

free_space_indicator = -1 # '.'

# make id map
id = 0
for i in range(len(disk_map)):
    if i % 2 == 0:
        id_map += [id for _ in range(int(disk_map[i]))]
        id += 1
    else:
        id_map += [free_space_indicator for _ in range(int(disk_map[i]))]

# swap free spaces
leftmost_free = 0
for i in range(len(id_map) - 1, -1, -1):
    if id_map[i] == free_space_indicator:
        continue

    while leftmost_free < i:
        if id_map[leftmost_free] == free_space_indicator:
            id_map[i], id_map[leftmost_free] = id_map[leftmost_free], id_map[i]
            break

        leftmost_free += 1

cum = 0
for i in range(len(id_map)):
    if id_map[i] != free_space_indicator:
        cum += i * id_map[i]

print(cum)