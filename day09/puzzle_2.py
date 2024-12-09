disk_map = open("input.txt").readlines()[0].rstrip('\n')
id_map = [] # list of tuple

free_space_indicator = -1 # '.'

# make id map
id = 0
for i in range(len(disk_map)):
    if i % 2 == 0:
        id_map.append((id, int(disk_map[i])))
        id += 1
    elif int(disk_map[i]) != 0: # ignore zero free spaces
    # else:
        id_map.append((free_space_indicator, int(disk_map[i])))

# swap free spaces
id_index = len(id_map) - 1

while id_index >= 0:
    if id_map[id_index][0] == free_space_indicator:
        id_index -= 1
        continue

    for j in range(id_index):
        if id_map[j][0] == free_space_indicator and id_map[j][1] >= id_map[id_index][1]:
            tmp_file = id_map[id_index]
            tmp_free = id_map[j]
            
            # move file
            id_map[j] = tmp_file

            # free space now at old file pos
            id_map[id_index] = (free_space_indicator, tmp_file[1])

            # if remaining space
            remaining = tmp_free[1] - tmp_file[1]
            if remaining != 0:
                id_map.insert(j+1, (free_space_indicator, remaining))
                id_index += 1 # fix index if insertion happens

            break
    
    id_index -= 1

pos = 0
ans = 0
for i in range(len(id_map)):
    for j in range(id_map[i][1]):
        if id_map[i][0] != free_space_indicator:
            ans += pos * id_map[i][0]
        pos += 1

print(ans)