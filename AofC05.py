'''

Advent of Code day 5
- James Cote

'''

def solve1():
    edges = [[] for _ in range(100)]
    line = input()
    while (line != ""):
        u, v = list(map(int, line.split("|")))
        edges[u].append(v)

        line = input()

    # Topological sort
    # Go through the cases
    ans = 0
    line = input()
    while (line != ""):
        pages = list(map(int, line.split(",")))
        p_set = set(pages)

        degree = [0 for _ in range(100)]
        for p in pages:
            for e in edges[p]:
                degree[e] += 1
        
        topo_sort = []
        for p in pages:
            if (degree[p] == 0):
                topo_sort.append(p)
        
        a = 0
        while (a < len(topo_sort)):
            node = topo_sort[a]
            for e in edges[node]:
                if (e in p_set):
                    degree[e] -= 1
                    if (degree[e] == 0):
                        topo_sort.append(e)
            a += 1
        print(pages, topo_sort)
        if (topo_sort == pages):
            ans += pages[(len(pages) - 1) // 2]

        line = input()
    print(ans)


def solve2():
    edges = [[] for _ in range(100)]
    line = input()
    while (line != ""):
        u, v = list(map(int, line.split("|")))
        edges[u].append(v)

        line = input()

    # Topological sort
    # Go through the cases
    ans = 0
    line = input()
    while (line != ""):
        pages = list(map(int, line.split(",")))
        p_set = set(pages)

        degree = [0 for _ in range(100)]
        for p in pages:
            for e in edges[p]:
                degree[e] += 1
        
        topo_sort = []
        for p in pages:
            if (degree[p] == 0):
                topo_sort.append(p)
        
        a = 0
        while (a < len(topo_sort)):
            node = topo_sort[a]
            for e in edges[node]:
                if (e in p_set):
                    degree[e] -= 1
                    if (degree[e] == 0):
                        topo_sort.append(e)
            a += 1
        print(pages, topo_sort)
        if (topo_sort != pages):
            ans += topo_sort[(len(topo_sort) - 1) // 2]

        line = input()
    print(ans)

def main():
    solve2()

if (__name__ == "__main__"):
    main()