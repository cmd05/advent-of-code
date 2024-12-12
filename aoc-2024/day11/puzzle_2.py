arrangement = [int(x) for x in open("input.txt").read().split('\n')[0].split(' ')]
num_blinks = 75

dict_arrangement = dict()

for num in arrangement:
    dict_arrangement.setdefault(num, 0)
    dict_arrangement[num] += 1

for i in range(num_blinks):
    items = dict_arrangement.items()
    new_dict = dict()
    
    for k,v in items:
        str_num = str(k)
        len_str = len(str_num)

        if k == 0:
            new_dict.setdefault(1, 0)
            new_dict[1] += v # 0 becomes 1
        elif len_str % 2 == 0:
            lh = int(str_num[:int(len_str / 2)])
            new_dict.setdefault(lh, 0)
            new_dict[lh] += v

            rh = int(str_num[int(len_str / 2):])
            new_dict.setdefault(rh, 0)
            new_dict[rh] += v
        else:
            k2 = k * 2024
            new_dict.setdefault(k2, 0)
            new_dict[k2] += v

    dict_arrangement = new_dict

cum_len = sum(dict_arrangement.values())

print(cum_len)