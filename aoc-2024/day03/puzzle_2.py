import re

# txt = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"
txt = ""

with open("d3p1.txt", 'r') as f:
    txt = f.read()

x = re.findall("mul\(\d\d?\d?,\d\d?\d?\)|don?'?t?\(\)", txt)

print(x) 
s = 0
en = True

for n in x:
    if n == "don't()":
        en = False
    elif n == "do()":
        en = True

    if en and "mul" in n:
        y = n.replace("mul(", "")
        y = y.replace(")","")
        
        l = y.split(",")
        s += int(l[0]) * int(l[1])
    
print(s)