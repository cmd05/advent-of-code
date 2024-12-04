# board[r][c]
board = []
word = "XMAS"

with open("d4.txt", 'r') as file:
	lines = file.readlines()
	
	for line in lines:
		board.append(list(line.rstrip("\n")))

nrows = len(board)
ncols = len(board[0])

def search(search_type, r, c, i):
	if i == len(word):
		return True
	
	if (r < 0 or c < 0 or
		r >= nrows or c >= ncols or
		board[r][c] != word[i]):
		return False
	
	if search_type == 'HF':
		res = search(search_type, r, c+1, i+1)
	elif search_type == 'HB':
		res = search(search_type, r, c-1, i+1)
	
	elif search_type == 'VU':
		res = search(search_type, r-1, c, i+1)
	elif search_type == 'VD':
		res = search(search_type, r+1, c, i+1)
	
	elif search_type == 'D1U':
		# first diagonal (\)
		res = search(search_type, r-1, c-1, i+1)
	elif search_type == 'D1D':
		res = search(search_type, r+1, c+1, i+1)
		
	elif search_type == 'D2U':
		# second diagonal (/)
		res = search(search_type, r-1, c+1, i+1)
	elif search_type == 'D2D':
		res = search(search_type, r+1, c-1, i+1)

	return res

count = 0

for r in range(nrows):
	for c in range(ncols):
		dirs = ['HF', 'HB', 'VU', 'VD', 'D1U', 'D1D', 'D2U', 'D2D']

		for d in dirs:
			if(search(d, r, c, 0)):
				count += 1

print(count)