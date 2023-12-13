#include <fstream>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

typedef std::vector<std::string> tiles;
typedef std::pair<int, int> coor;

coor find_start(tiles& t) {
    int x, y;
    for (y = 0; y < t.size(); y++) {
        for (x = 0; x < t[y].size(); x++) {
            if (t[y][x] == 'S') {
                return {x, y};
            }
        }
    }
    return {};
}

std::pair<coor, coor> find_adj(tiles& t, coor c) {
    std::vector<coor> coords;
    std::string left = "-FLS", right = "-J7S", up = "|7FS", down = "|JLS";

    auto [x, y] = c;

    if (x > 0 && left.contains(t[y][x - 1]) &&
        (right.contains(t[y][x]) || t[y][x] == 'S')) {
        coords.emplace_back(x - 1, y);
    }
    if (x < t[y].size() - 1 && right.contains(t[y][x + 1]) &&
        (left.contains(t[y][x]) || t[y][x] == 'S')) {
        coords.emplace_back(x + 1, y);
    }
    if (y < t.size() - 1 && down.contains(t[y + 1][x]) &&
        (up.contains(t[y][x]) || t[y][x] == 'S')) {
        coords.emplace_back(x, y + 1);
    }
    if (y > 0 && up.contains(t[y - 1][x]) &&
        (down.contains(t[y][x]) || t[y][x] == 'S')) {
        coords.emplace_back(x, y - 1);
    }

    return {coords[0], coords[1]};
}

std::set<coor> find_loop(tiles& t, coor start) {
    std::set<coor> res;
    coor current = start;

    while (!res.contains(current)) {
        res.insert(current);
        auto [c1, c2] = find_adj(t, current);
        current = res.contains(c1) ? c2 : c1;
    }

    return res;
}

tiles read_tiles(std::fstream& fs) {
    tiles res;

    for (std::string line; getline(fs, line);) {
        res.push_back(line);
    }

    return res;
}

int main() {
    std::fstream input("input.txt");

    tiles t = read_tiles(input);

    input.close();

    coor start = find_start(t);
    auto loop = find_loop(t, start);

    std::cout << loop.size() / 2 << std::endl;

    return 0;
}
