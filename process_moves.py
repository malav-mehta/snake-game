import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import datetime

filename = "moves.txt"
table_format = []
plt.style.use("seaborn-whitegrid")

with open(filename, "r") as f:
    length_to_moves = {}

    for line in f.readlines():
        l, k = map(int, line.strip().split())
        length_to_moves[l] = length_to_moves.get(l, []) + [k]

    for length in length_to_moves:
        length_to_moves[length] = sum(
            length_to_moves[length]) / len(length_to_moves[length])
        table_format.append(f"{length} & {round(length_to_moves[length], 4)}")

    x = np.array(list(map(int, length_to_moves.keys())))
    y = np.array(list(map(float, length_to_moves.values())))
    coef = np.polyfit(x, y, 5)
    poly = np.poly1d(coef)

    new_x = np.linspace(x[0], x[-1])
    new_y = poly(new_x)
    plt.plot(x, y, "o", color="blue")
    plt.plot(new_x, new_y, color="red")

    plt.xlabel("Length (l)")
    plt.ylabel("Average Moves Required To Reach l + 1 (k)")
    plt.title("BFS: Mean Moves Required To Increase Snake Length")
    plt.savefig(datetime.datetime.now().strftime("renders/%Y-%m-%d %H-%M-%S"))

with open(filename, "w") as f:
    f.write("\n\hline\n".join(table_format))
