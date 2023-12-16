#include <algorithm>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

typedef std::vector<std::string> grid;

std::set<std::tuple<int, int, int, int>> done{};
std::set<std::pair<int, int>> mirrors{};

void add(std::vector<std::tuple<int, int, int, int>>& stack,
         std::tuple<int, int, int, int> t) {
    if (!done.contains(t)) stack.push_back(t);
}

void find_energized(grid& g) {
    std::vector<std::tuple<int, int, int, int>> stack{};

    stack.push_back({0, 0, 1, 0});

    b:
        if (stack.empty()) return;

        while (done.contains(stack.back())) stack.pop_back();

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
                        add(stack, {x + 1, y, 1, 0});
                        add(stack, {x - 1, y, -1, 0});
                        goto b;
                    }
                    break;
                case '|':
                    mirrors.insert({x, y});
                    if (y_step == 0) {
                        add(stack, {x, y + 1, 0, 1});
                        add(stack, {x, y - 1, 0, -1});
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

    find_energized(g);

    uint64_t res = 0;

    for (auto line : g) {
        std::cout << line << std::endl;
        res += std::count_if(line.begin(), line.end(),
                             [](char ch) { return ch == '#'; });
    }

    std::cout << res + mirrors.size() << std::endl;

    return 0;
}
