# board[r][c]
board = []
word = "XMAS"

with open("d4.txt", 'r') as file:
	lines = file.readlines()
	
	for line in lines:
		board.append(list(line.rstrip("\n")))

nrows = len(board)
ncols = len(board[0])

def in_bound(r, c):
	return r >= 0 and r < nrows and c >= 0 and c < ncols

count = 0

for r in range(nrows):
	for c in range(ncols):
		if board[r][c] == 'A':
			if(
			# first diagonal (\)
			in_bound(r-1, c-1) and in_bound(r+1, c+1) 
				and (board[r-1][c-1] in "MS" and board[r+1][c+1] in "MS" and board[r-1][c-1] != board[r+1][c+1])
			and
			# second diagonal (/)
			in_bound(r+1, c-1) and in_bound(r-1, c+1) 
				and (board[r+1][c-1] in "MS" and board[r-1][c+1] in "MS" and board[r+1][c-1] != board[r-1][c+1])
			):
				count += 1

print(count)