#include <algorithm>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

typedef std::vector<std::string> grid;

void add(std::vector<std::tuple<int, int, int, int>>& stack,
         std::set<std::tuple<int, int, int, int>> done,
         std::tuple<int, int, int, int> t) {
    if (!done.contains(t)) stack.push_back(t);
}

uint64_t find_energized(grid g, int x_init, int y_init, int x_step_init,
                        int y_step_init) {
    std::vector<std::tuple<int, int, int, int>> stack{};
    std::set<std::tuple<int, int, int, int>> done{};
    std::set<std::pair<int, int>> mirrors{};

    stack.push_back({x_init, y_init, x_step_init, y_step_init});

b:
    while (done.contains(stack.back())) stack.pop_back();

    if (stack.empty()) {
        uint64_t res = 0;

        for (auto line : g) {
            res += std::count_if(line.begin(), line.end(),
                                 [](char ch) { return ch == '#'; });
        }

        return res + mirrors.size();
    }

    done.insert(stack.back());
    auto [x, y, x_step, y_step] = stack.back();
    assert(abs(x_step) + abs(y_step) == 1);
    stack.pop_back();

    while (x >= 0 && x < g[0].size() && y >= 0 && y < g.size()) {
        int tmp;
        switch (g[y][x]) {
            case '.':
                g[y][x] = '#';
                break;
            case '/':
                done.insert({x, y, y_step, x_step});
                mirrors.insert({x, y});
                tmp = x_step;
                x_step = -y_step;
                y_step = -tmp;
                break;
            case '\\':
                done.insert({x, y, y_step, x_step});
                mirrors.insert({x, y});
                tmp = x_step;
                x_step = y_step;
                y_step = tmp;
                break;
            case '-':
                mirrors.insert({x, y});
                if (x_step == 0) {
                    add(stack, done, {x + 1, y, 1, 0});
                    add(stack, done, {x - 1, y, -1, 0});
                    goto b;
                }
                break;
            case '|':
                mirrors.insert({x, y});
                if (y_step == 0) {
                    add(stack, done, {x, y + 1, 0, 1});
                    add(stack, done, {x, y - 1, 0, -1});
                    goto b;
                }
                break;
        }

        x += x_step;
        y += y_step;
    }
    goto b;
}

int main() {
    std::fstream input("input.txt");

    grid g;
    for (std::string line; std::getline(input, line);) {
        g.push_back(line);
    }

    input.close();

    uint64_t energized = 0;

    for (int y = 0; y < g.size(); y++) {
        for (int x = 0; x < g[0].size(); x++) {
            if (y == 0)
                energized = std::max(energized, find_energized(g, x, y, 0, 1));
            if (y == g.size() - 1)
                energized = std::max(energized, find_energized(g, x, y, 0, -1));
            if (x == 0)
                energized = std::max(energized, find_energized(g, x, y, 1, 0));
            if (x == g[0].size() - 1)
                energized = std::max(energized, find_energized(g, x, y, -1, 0));
        }
    }

    std::cout << energized << std::endl;
    return 0;
}
