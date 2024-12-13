from sympy import *

def get_int(s):
    return int(''.join(filter(str.isdigit, s)))

sym_x, sym_y = symbols('x y')

inp = [x for x in open("input.txt").read().split('\n') if x]
puzzles = [inp[i:i+3] for i in range(0, len(inp), 3)]
max_press = 100

for i in range(len(puzzles)):
    puzzles[i] = [(get_int(subl[0]), get_int(subl[1])) for subl in (spl for spl in (s.split(',') for s in puzzles[i]))]

cum_tokens = 0

for puzzle in puzzles:
    eq1 = Eq(puzzle[0][0]*sym_x + puzzle[1][0]*sym_y, puzzle[2][0])
    eq2 = Eq(puzzle[0][1]*sym_x + puzzle[1][1]*sym_y, puzzle[2][1])

    solution = solve((eq1, eq2), (sym_x, sym_y))

    if (solution[sym_x].is_integer and 0 <= solution[sym_x] <= max_press 
        and solution[sym_y].is_integer and 0 <= solution[sym_y] <= max_press):
        cum_tokens += solution[sym_x] * 3 + solution[sym_y]
        # print(solution)

print(cum_tokens)