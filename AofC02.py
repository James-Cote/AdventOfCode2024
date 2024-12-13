'''

Advent of Code day 2
- James Cote

'''

def solve1():
    in_str = input()
    ans = 0
    while (in_str != ""):
        nums = list(map(int, in_str.split(" ")))
        pos = 1
        if (nums[1] < nums[0]):
            pos = -1
        
        safe = True
        for i in range(len(nums) - 1):
            dist = pos * (nums[i+1] - nums[i])
            if (dist < 1 or dist > 3):
                safe = False
                break
        
        ans += safe == True

        in_str = input()
    print(ans)

def isSafe(nums):
    pos = 1
    if (nums[1] < nums[0]):
        pos = -1
    
    safe = True
    for i in range(len(nums) - 1):
        dist = pos * (nums[i+1] - nums[i])
        if (dist < 1 or dist > 3):
            safe = False
            break
    return safe

def solve2():
    in_str = input()
    ans = 0
    while (in_str != ""):
        nums = list(map(int, in_str.split(" ")))
        
        safe = isSafe(nums)

        i = 0
        while (not safe and i < len(nums)):
            # Test the removal of an item
            safe = isSafe(nums[:i] + nums[i+1:])
            i += 1
        ans += safe == True

        in_str = input()
    print(ans)

def main():
    solve2()

if (__name__ == "__main__"):
    main()