'''

Day 7 of Advent of Code
- James Cote

'''

def getAns(nums, ans, cur, i):
    if (i >= len(nums)):
        ans.append(cur)
        return
    
    getAns(nums, ans, cur + nums[i], i + 1)
    getAns(nums, ans, cur * nums[i], i + 1)

def solve1():
    line = input()
    ans_sum = 0
    while (line != ""):
        sp = line.split(" ")
        sp[0] = sp[0][:-1]
        nums = list(map(int, sp))
        
        ans = []
        getAns(nums, ans, nums[1], 2)
        
        valid = False
        for i in ans:
            if (i == nums[0]):
                valid = True
        if (valid):
            ans_sum += nums[0]
        
        line = input()
    print(ans_sum)

def getAns2(nums, ans, cur, i):
    if (i >= len(nums)):
        ans.append(cur)
        return
    
    getAns2(nums, ans, cur + nums[i], i + 1)
    getAns2(nums, ans, cur * nums[i], i + 1)
    getAns2(nums, ans, int(str(cur) + str(nums[i])), i + 1)

def solve2():
    line = input()
    ans_sum = 0
    while (line != ""):
        sp = line.split(" ")
        sp[0] = sp[0][:-1]
        nums = list(map(int, sp))
        
        ans = []
        getAns2(nums, ans, nums[1], 2)
        
        valid = False
        for i in ans:
            if (i == nums[0]):
                valid = True
        if (valid):
            ans_sum += nums[0]
        
        line = input()
    print(ans_sum)


def main():
    solve2()

if (__name__ == "__main__"):
    main()