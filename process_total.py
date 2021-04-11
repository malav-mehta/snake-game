filename = "total_moves.txt"

with open(filename, "r") as f:
    L = M = T = W = WM = 0

    for line in f.readlines():
        l, m = map(int, line.strip().split())
        if (l == 99):
            W += 1
            WM += m
        L += l
        M += m
        T += 1

    print(L / T, M / T, W / T * 100, (WM / W) if W != 0 else 0)
