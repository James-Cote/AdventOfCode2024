'''

Advent of Code day 4
- James Cote

'''

def check(word):
    if (word == "XMAS"): return 1
    word = word[::-1]
    if (word == "XMAS"): return 1
    return 0

def solve1():
    grid = []
    line = input()
    while (line != ""):
        grid.append(line)
        line = input()
    
    ans = 0
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            # Horizontal search
            if (j <= len(grid[i]) - 4):
                word = grid[i][j:j+4]
                ans += check(word)
            # Vertical
            if (i <= len(grid) - 4):
                word = ""
                for k in range(4):
                    word = word + grid[i+k][j]
                ans += check(word)
            # Diagonals
            if (j <= len(grid[i]) - 4 and i <= len(grid) - 4):
                word = ""
                for k in range(4):
                    word = word + grid[i+k][j+k]
                ans += check(word)
            if (j <= len(grid[i]) - 4 and i <= len(grid) - 4):
                word = ""
                for k in range(4):
                    word = word + grid[i+k][j+3-k]
                ans += check(word)
    print(ans)


def solve2():
    grid = []
    line = input()
    while (line != ""):
        grid.append(line)
        line = input()
    
    ans = 0
    for i in range(1, len(grid) - 1):
        for j in range(1, len(grid[i]) - 1):
            # Check Cross
            if (grid[i][j] == 'A'):
                word1 = grid[i-1][j-1] + grid[i+1][j+1]
                if (not(word1 == "MS" or word1 == "SM")): continue
                word2 = grid[i-1][j+1] + grid[i+1][j-1]
                if (not(word2 == "MS" or word2 == "SM")): continue
                ans += 1
    print(ans)

def main():
    solve2()

if (__name__ == "__main__"):
    main()