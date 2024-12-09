disk_map = open("input.txt").readlines()[0].rstrip('\n')
id_map = [] # list of tuple

free_space_indicator = -1 # '.'

# make id map
id = 0
for i in range(len(disk_map)):
    if i % 2 == 0:
        id_map.append((id, int(disk_map[i])))
        id += 1
    # elif int(disk_map[i]) != 0: # assuming free spaces only occur at odd positions
    else:
        id_map.append((free_space_indicator, int(disk_map[i])))

# print(id_map)
# print(len(id_map))
# exit()

# print(id_map)
# unswapped_id_map = id_map

# no need of recursively checking from last id each time according to example

# swap free spaces
i = len(id_map) - 1
for i in range(len(id_map) - 1, -1, -1):
    if id_map[i][0] == free_space_indicator:
        continue

    # print(id_map[i])

    for j in range(i):
        if id_map[j][0] == free_space_indicator and id_map[j][1] >= id_map[i][1]:
            tmp_file = id_map[i]
            tmp_free = id_map[j]
            
            # print("move", id_map[i], "to", id_map[j])

            # free space now at old file pos (step not required tho)
            # we can merge that free space too (not reqd)
            id_map[i] = (free_space_indicator, tmp_file[1])

            # move file
            id_map[j] = tmp_file

            # if remaining space
            remaining = tmp_free[1] - tmp_file[1]
            if remaining != 0:
                id_map.insert(j+1, (free_space_indicator, remaining))
                # fix index if insertion happens
                i += 1

            # print("after move", id_map)
            # if(tmp_file[0] == 4): 
            #     print("exit")
            #     exit()
            break

# print(id_map)

pos = 0
cum = 0
for i in range(len(id_map)):
    if id_map[i][1] == 0:
        print("zero")
    for j in range(id_map[i][1]):
        if id_map[i][0] != free_space_indicator:
            cum += pos * id_map[i][0]
        pos += 1

print(cum)
# 6402760149876 too high
# 6363913128533 corr