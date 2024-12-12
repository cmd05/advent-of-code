arrangement = [int(x) for x in open("input.txt").read().split('\n')[0].split(' ')]
num_blinks = 25

for i in range(num_blinks):
    j = 0
    while j < len(arrangement):
        str_num = str(arrangement[j])
        len_str = len(str_num)

        if arrangement[j] == 0:
            arrangement[j] = 1
        elif len_str % 2 == 0:
            # print(int(str_num[:int(len_str / 2)]), int(str_num[int(len_str / 2):]))
            arrangement[j] = int(str_num[:int(len_str / 2)])
            arrangement.insert(j + 1, int(str_num[int(len_str / 2):])) # using int() will remove trailing zeroes
            j += 1 # fix index to next number after insertion
        else:
            arrangement[j] *= 2024
        
        j += 1
    
    # print(arrangement)

print(len(arrangement))