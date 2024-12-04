import re

txt = ""

with open("d3p1.txt", 'r') as f:
    txt = f.read()

x = re.findall("mul\(\d\d?\d?,\d\d?\d?\)", txt)
s = 0

for n in x:
    y = n.replace("mul(", '')
    y = y.replace(")", '')
    
    l = y.split(",")
    s += int(l[0]) * int(l[1])
    
print(s)