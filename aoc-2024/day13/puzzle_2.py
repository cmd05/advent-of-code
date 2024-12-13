from sympy import *

def get_int(s):
    return int(''.join(filter(str.isdigit, s)))

sym_x, sym_y = symbols('x y')

inp = [x for x in open("input.txt").read().split('\n') if x]
puzzles = [inp[i:i+3] for i in range(0, len(inp), 3)]

add_prize = 10000000000000
cum_tokens = 0

for i in range(len(puzzles)):
    puzzles[i] = [(get_int(subl[0]), get_int(subl[1])) for subl in (spl for spl in (s.split(',') for s in puzzles[i]))]

for puzzle in puzzles:
    eq1 = Eq(puzzle[0][0]*sym_x + puzzle[1][0]*sym_y, add_prize + puzzle[2][0])
    eq2 = Eq(puzzle[0][1]*sym_x + puzzle[1][1]*sym_y, add_prize + puzzle[2][1])

    solution = solve((eq1, eq2), (sym_x, sym_y))

    f1, f2 = float(solution[sym_x]), float(solution[sym_y])
    i1, i2 = int(f1), int(f2)

    if (i1 >= 0 and i2 >= 0 and i1 == f1 and i2 == f2):
        cum_tokens += i1 * 3 + i2

print(cum_tokens)