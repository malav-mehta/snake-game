# snake-game

## About

An automated snake game player build with the intent of creating a program prioritizing minimizing the time required to beat the game. The project itself is built in C++. The analysis of the results is conducted in Python with numpy and matplotlib.

### Approach

The approach undertaken by this project is explained in [this report](/report/math_ia.pdf). This project was submitted as an internal assessment for HL Math.

### References

- Inspiration: [CodeBullet](https://www.youtube.com/watch?v=tjQIO1rqTBE&ab_channel=CodeBullet)
- Hamiltonian Cycle Heuristic: [Chuyang Liu](https://github.com/chuyangliu/snake/blob/master/docs/algorithms.md#hamilton-solver)

## Running locally

First, clone the repo:

```shell
$ git clone https://github.com/malav-mehta/snake-game.git
$ cd snake-game
```

Next, build the project:

```shell
$ g++ main.cpp -std=c++11 -o snake
```

### Usage

To see the bot in action, run:

```shell
$ ./snake
```

To collect data by running the game `x` times (no GUI), run:

```shell
$ ./snake [x]
```

## Tech stack

- [C++](https://www.cplusplus.com/)
- [Python](https://www.python.org/)
- [Matplotlib](https://matplotlib.org/)
- [Numpy](https://numpy.org/)

If you find any bugs or have any questions, email me: [malavhmehta@outlook.com](mailto:malavhmehta@outlook.com).
