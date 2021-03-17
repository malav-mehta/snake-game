/**
 * Snake Game AI
 * HL Math Internal Assessment
 * 
 * Author: Malav Mehta
 * Date: March 7, 2021
 */
#include <bits/stdc++.h>

#define LIMIT 25
#define SPEED 20

using namespace std;
bool BFS_ONLY = false;

struct Node {
  int x, y;
  static Node up, down, left, right;

  Node() {
    x = 0;
    y = 0;
  }

  Node(int _x, int _y) {
    x = _x;
    y = _y;
  }

  Node operator+(Node& o) const {
    return Node(x + o.x, y + o.y);
  }

  Node operator-(Node& o) const {
    return Node(x - o.x, y - o.y);
  }

  bool operator==(Node& o) const {
    return x == o.x && y == o.y;
  }

  void put() const {
    printf("(%d, %d)\n", x, y);
  }

  vector<Node> adj() const {
    vector<Node> adj_nodes;
    adj_nodes.push_back(*this + up);
    adj_nodes.push_back(*this + down);
    adj_nodes.push_back(*this + left);
    adj_nodes.push_back(*this + right);
    return adj_nodes;
  }

  Node opp() const {
    if (*this == up) return down;
    if (*this == down) return up;
    if (*this == left) return right;
    if (*this == right) return left;
    return Node();
  }
};

Node Node::up(-1, 0);
Node Node::down(1, 0);
Node Node::left(0, -1);
Node Node::right(0, 1);

template <class T>
struct Table {
  T _table[LIMIT][LIMIT];
  Table() {}

  void clear() {
    memset(_table, 0, sizeof(_table));
  }

  T& operator[](Node u) {
    return _table[u.x][u.y];
  }
};

struct Game {
  int size, gui, cycle_size;
  Table<int> grid, vis;
  Table<Node> cycle;
  vector<Node> snake;
  Node apple;

  Game(int _size, int _gui) {
    size = _size;
    gui = _gui;
    srand(time(NULL));
  }

  bool is_valid(Node u) const {
    return 0 <= u.x && u.x < size &&
           0 <= u.y && u.y < size;
  }

  void gen_apple() {
    apple = snake.back();

    while (grid[apple]) {
      apple.x = rand() % size;
      apple.y = rand() % size;
    }

    grid[apple] = 2;
  }

  void init() {
    grid.clear();
    snake.clear();
    cycle_size = 0;

    snake.push_back(Node(0, 0));
    for (Node u : snake)
      grid[u] = 1;

    gen_apple();
  }

  bool tick(Node d) {
    Node nxt = snake.back() + d;

    if (is_valid(nxt) && grid[nxt] != 1) {
      snake.push_back(nxt);

      if (grid[nxt] == 2)
        gen_apple();
      else {
        Node tail = snake[0];
        snake.erase(snake.begin());
        grid[tail] = 0;
      }

      grid[nxt] = 1;
      return true;
    }

    return false;
  }

  vector<Node> dir_path(vector<Node> path) {
    vector<Node> new_path;

    if (path.size() > 0)
      for (int i = 0; i < path.size() - 1; ++i)
        new_path.push_back(path[i + 1] - path[i]);

    return new_path;
  }

  vector<Node> pos_path(vector<Node> path) {
    Node cur = snake.back();
    vector<Node> new_path;
    new_path.push_back(cur);

    for (Node u : path) {
      cur = cur + u;
      new_path.push_back(cur);
    }

    return new_path;
  }

  vector<Node> shortest_path(Node des) {
    queue<vector<Node> > q;
    q.push({snake.back()});
    vis.clear();

    for (Node u : snake)
      vis[u] = 1;
    vis[des] = 0;

    while (!q.empty()) {
      vector<Node> path = q.front();
      q.pop();

      if (path.back() == des)
        return path;

      for (Node u : path.back().adj()) {
        if (is_valid(u) && !vis[u]) {
          vis[u] = 1;
          vector<Node> new_path(path);
          new_path.push_back(u);
          q.push(new_path);
        }
      }
    }

    return {};
  }

  vector<Node> longest_path(Node des) {
    vector<Node> path = shortest_path(des);
    vis.clear();
    for (Node u : path)
      vis[u] = 1;
    for (Node u : snake)
      vis[u] = 1;
    path = dir_path(path);
    if (path.size() < 1)
      return path;

    int i = 0;
    Node cur = snake.back();
    while (true) {
      Node cur_dir = path[i];
      Node nxt = cur + cur_dir;
      vector<Node> tests;

      if (cur_dir == Node::left || cur_dir == Node::right) {
        tests.push_back(Node::up);
        tests.push_back(Node::down);
      }

      else {
        tests.push_back(Node::left);
        tests.push_back(Node::right);
      }

      bool extended = false;
      for (Node test_dir : tests) {
        Node cur_test = cur + test_dir;
        Node nxt_test = nxt + test_dir;

        if (is_valid(cur_test) && is_valid(nxt_test) && !vis[cur_test] && !vis[nxt_test]) {
          vis[cur_test] = 1;
          vis[nxt_test] = 1;
          path.insert(path.begin() + i, test_dir);
          path.insert(path.begin() + i + 2, test_dir.opp());
          extended = true;
          break;
        }
      }

      if (!extended) {
        cur = nxt;
        ++i;
        if (i >= path.size())
          break;
      }
    }

    return path;
  }

  void build_cycle() {
    cycle.clear();
    vector<Node> path_dir = longest_path(snake[0]), snake_path = dir_path(snake);
    for (Node u : snake_path)
      path_dir.push_back(u);

    Node cur = snake.back();
    for (Node u : path_dir) {
      cycle[cur] = u;
      cur = cur + u;
    }
    cycle_size = path_dir.size();
  }

  Node next_dir() {
    if (BFS_ONLY || snake.size() < size) {
      vector<Node> path = dir_path(shortest_path(apple));
      if (path.size() > 0)
        return path[0];
      return Node();
    }
    if (cycle_size < (size * size))
      build_cycle();
    return cycle[snake.back()];
  }

  void put() {
    system("clear");
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        Node u(i, j);
        if (snake.back() == u)
          printf("\033[1;32m@\033[0m");
        else if (grid[u] == 1)
          printf("\033[1;32m#\033[0m");
        else if (grid[u] == 2)
          printf("\033[1;31m%d\033[0m", (int)snake.size() % 10);
        else
          printf(" ");
      }
      printf("\n");
    }
  }

  void loop() {
    bool over = false;
    int cnt = size * size - 1;

    while (!over && snake.size() < cnt) {
      auto start = chrono::high_resolution_clock::now();
      if (!tick(next_dir()))
        over = true;
      auto elapsed = chrono::high_resolution_clock::now() - start;
      long long time = chrono::duration_cast<chrono::microseconds>(elapsed).count();

      if (gui) {
        put();
        printf("\n\033[1;34m==>\033[0m length: %d\n\033[1;34m==>\033[0m time: %lld\n", (int)snake.size(), time);
        this_thread::sleep_for(chrono::milliseconds(1000 / SPEED));
      }
    }
  }

  int run() {
    init();
    loop();
    return (int)snake.size();
  }
};

void tester(int size, int rounds) {
  ofstream of;
  of.open("data.txt", ios::out | ios::trunc);
  of << rounds << "\n";
  of << size << "\n";
  Game* g = new Game(size, 0);
  for (int i = 0; i < rounds; ++i)
    of << g->run() << "\n";
  of.close();
  system("python3 process.py");
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    BFS_ONLY = true;
    tester(10, stol(argv[1], NULL, 10));
  }

  else {
    Game* g = new Game(10, 1);
    g->run();
  }
  return 0;
}