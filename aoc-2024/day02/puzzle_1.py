with open("d2p1.txt", 'r') as file:
    lines = file.readlines()
    nsafe = 0
    
    for line in lines:
        l = line.rstrip('\n').split(' ')
        inc = int(l[0]) < int(l[1]) # is increasing
        
        for i in range(len(l) - 1):
            diff = int(l[i+1]) - int(l[i])
            
            if inc and diff < 0:
                break
            if not inc and diff > 0:
                break
            if abs(diff) < 1 or abs(diff) > 3:
                break
        else:
            nsafe += 1
    
    print(nsafe)