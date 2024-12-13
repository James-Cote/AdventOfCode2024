'''

Advent of Code day 3
- James Cote

'''


def solve1():
    s = input()
    ans = 0
    while (s != ""):
        for i in range(4, len(s)):
            if (s[i-4:i] == "mul("):
                j = i + 1
                while (j < i + 9 and j < len(s) and s[j] != ')'):
                    j += 1
                if (j < len(s) and s[j] == ')'):
                    # Check if it is a valid mult
                    mult = s[i:j].split(',')
                    if (len(mult) == 2 and mult[0].isdigit() and mult[1].isdigit()):
                        ans += int(mult[0]) * int(mult[1])

        s = input()
    print(ans)

def solve2():
    s = input()
    ans = 0
    enabled = True
    while (s != ""):
        for i in range(4, len(s)):
            if (s[i-4:i] == "mul(" and enabled):
                j = i + 1
                while (j < i + 9 and j < len(s) and s[j] != ')'):
                    j += 1
                if (j < len(s) and s[j] == ')'):
                    # Check if it is a valid mult
                    mult = s[i:j].split(',')
                    if (len(mult) == 2 and mult[0].isdigit() and mult[1].isdigit()):
                        ans += int(mult[0]) * int(mult[1])
            if(s[i-4:i] == "do()"):
                enabled = True
            if(i >= 7 and s[i-7:i] == "don't()"):
                enabled = False
        s = input()
    print(ans)

def main():
    solve2()

if (__name__ == "__main__"):
    main()