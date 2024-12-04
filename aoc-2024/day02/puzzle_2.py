with open("d2p1.txt", 'r') as file:
    lines = file.readlines()
    nsafe = 0
    
    for line in lines:
        l = line.rstrip('\n').split(' ')
        inc = int(l[0]) < int(l[1]) # is increasing
        wrong = 0

        for i in range(len(l) - 1):
            diff = int(l[i+1]) - int(l[i])
            
            if abs(diff) < 1 or abs(diff) > 3:
                wrong += 1
            elif inc and diff < 0:
                wrong += 1
            elif not inc and diff > 0:
                wrong += 1
            
            if wrong > 1:
                break
        else:
            nsafe += 1
    
    print(nsafe)