with open("day1p1.txt", "r") as file:
    lines = file.readlines()
    l1 = []
    l2 = []

    for line in lines:
        l = line.rstrip("\n").split("   ")
        
        l1.append(int(l[0]))
        l2.append(int(l[1]))

    score = 0

    for i in range(len(l1)):
        score += l1[i] * l2.count(l1[i])
    
    print(score)