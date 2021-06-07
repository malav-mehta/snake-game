import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import datetime

filename = "data.txt"
output = "format.txt"
plt.style.use("seaborn-whitegrid")

with open(filename, "r") as f:
    rounds = int(f.readline().strip())
    size = int(f.readline().strip())

    x = np.arange(0, size * size + 1, 1)
    y = np.zeros(size * size + 1)
    scores = []

    for line in f.readlines()[2:]:
        score = int(line.strip())
        scores.append(score)
        y[score] += 1

    mu, std = norm.fit(np.array(scores))
    plt.bar(x, y / rounds, width=1, align="edge", color="blue")

    x_line = np.arange(0, size * size + 1, 1)
    y_line = norm.pdf(x_line, mu, std)
    plt.plot(x_line, y_line, marker="o", color="red")

    textstr = '\n'.join((
        r'$\mu=%.2f$' % mu,
        r'$\sigma=%.2f$' % std,
        r'$n=%d$' % rounds,))
    plt.text(1, 0.06, textstr)

    plt.xlabel("Terminating Score")
    plt.ylabel("Probability")
    plt.title("Probability Histogram of Terminating Scores (Size: %d)" % size)
    plt.savefig(datetime.datetime.now().strftime("renders/%Y-%m-%d %H-%M-%S"))

    with open(output, "w") as o:
        o.write("".join(list(map(str, zip(x, np.round(y/rounds, 4))))))
