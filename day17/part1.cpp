#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <vector>

typedef std::vector<std::string> city_map;

struct node {
    node(int x, int y) : x(x), y(y), up(3), down(3), left(3), right(3) {}

    node(int x, int y, int up, int down, int left, int right)
        : x(x), y(y), up(up), down(down), left(left), right(right) {}

    int x, y, up, down, left, right;

    friend bool operator<(const node& lhs, const node& rhs) {
        return std::tie(lhs.x, lhs.y, lhs.up, lhs.down, lhs.left, lhs.right) <
               std::tie(rhs.x, rhs.y, rhs.up, rhs.down, rhs.left, rhs.right);
    }
};

void load_map(city_map& m, std::fstream& fs) {
    for (std::string line; getline(fs, line);) {
        m.push_back(line);
    }
}

std::set<node> get_adj(city_map& m, node& n) {
    std::set<node> res;

    if (n.x > 0 && n.left > 0 && n.right == 3) {
        res.insert({n.x - 1, n.y, 3, 3, n.left - 1, 3});
    }

    if (n.x < m[0].size() - 1 && n.right > 0 && n.left == 3) {
        res.insert({n.x + 1, n.y, 3, 3, 3, n.right - 1});
    }

    if (n.y > 0 && n.up > 0 && n.down == 3) {
        res.insert({n.x, n.y - 1, n.up - 1, 3, 3, 3});
    }

    if (n.y < m.size() - 1 && n.down > 0 && n.up == 3) {
        res.insert({n.x, n.y + 1, 3, n.down - 1, 3, 3});
    }

    return res;
}

int find_path(city_map& m, int x_start, int y_start, int x_end, int y_end) {
    std::map<node, int> distances;

    distances[{x_start, y_start}] = m[y_start][x_start] - 48;

    auto node_cmp = [&distances](const node& l, const node& r) {
        return distances[l] > distances[r];
    };

    std::priority_queue<node, std::vector<node>, decltype(node_cmp)> queue(
        node_cmp);

    queue.push({x_start, y_start});

    while (!queue.empty()) {
        auto n = queue.top();
        queue.pop();

        for (node adj : get_adj(m, n)) {
            int t_d = distances[n] + m[adj.y][adj.x] - 48;

            if (!distances.contains(adj) || t_d < distances[adj]) {
                distances[adj] = t_d;
                queue.push(adj);
            }
        }
    }

    int res = std::numeric_limits<int>::max();
    for (auto& [n, d] : distances) {
        if (n.x == x_end && n.y == y_end) res = std::min(res, d);
    }

    return res;
}

int main() {
    std::fstream input("input.txt");

    city_map m;
    load_map(m, input);

    input.close();

    std::cout << find_path(m, 0, 0, m[0].size() - 1, m.size() - 1) << std::endl;

    return 0;
}
