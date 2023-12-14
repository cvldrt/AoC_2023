#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

typedef std::vector<std::string> platform;

struct hash {
    std::size_t operator()(const std::vector<std::string>& vec) const {
        std::size_t result = 0;

        for (const auto& str : vec) {
            result ^= std::hash<std::string>{}(str) + 0x9e3779b9 +
                      (result << 6) + (result >> 2);
        }

        return result;
    }
};

std::unordered_map<platform, int, hash> cache;

platform parse(std::fstream& fs) {
    platform res;

    for (std::string line; std::getline(fs, line);) {
        res.push_back(line);
    }

    return res;
}

void tilt_north(platform& p) {
    std::vector<int> first_empty(p[0].size(), 0);

    for (int y = 0; y < p.size(); y++) {
        for (int x = 0; x < p[y].size(); x++) {
            switch (p[y][x]) {
                case 'O':
                    p[y][x] = '.';
                    p[first_empty[x]][x] = 'O';
                    first_empty[x]++;
                    break;
                case '#':
                    first_empty[x] = y + 1;
            }
        }
    }
}

void tilt_south(platform& p) {
    std::vector<int> first_empty(p[0].size(), p.size() - 1);

    for (int y = p.size() - 1; y >= 0; y--) {
        for (int x = 0; x < p[y].size(); x++) {
            switch (p[y][x]) {
                case 'O':
                    p[y][x] = '.';
                    p[first_empty[x]][x] = 'O';
                    first_empty[x]--;
                    break;
                case '#':
                    first_empty[x] = y - 1;
            }
        }
    }
}

void tilt_west(platform& p) {
    std::vector<int> first_empty(p.size(), 0);

    for (int x = 0; x < p[0].size(); x++) {
        for (int y = 0; y < p.size(); y++) {
            switch (p[y][x]) {
                case 'O':
                    p[y][x] = '.';
                    p[y][first_empty[y]] = 'O';
                    first_empty[y]++;
                    break;
                case '#':
                    first_empty[y] = x + 1;
            }
        }
    }
}

void tilt_east(platform& p) {
    std::vector<int> first_empty(p.size(), p[0].size() - 1);

    for (int x = p[0].size() - 1; x >= 0; x--) {
        for (int y = 0; y < p.size(); y++) {
            switch (p[y][x]) {
                case 'O':
                    p[y][x] = '.';
                    p[y][first_empty[y]] = 'O';
                    first_empty[y]--;
                    break;
                case '#':
                    first_empty[y] = x - 1;
            }
        }
    }
}

uint64_t calc_load(platform& p) {
    uint64_t res = 0;
    int m = p.size();

    for (auto line : p) {
        res += std::count(line.begin(), line.end(), 'O') * m--;
    }

    return res;
}

void rotate(platform& p, uint64_t rotations) {
    bool found_loop = false;

    for (uint64_t n = 0; n < rotations; n++) {
        if (cache.contains(p) && !found_loop) {
            found_loop = true;

            int loop_size = n - cache[p];
            n += (rotations / loop_size) * loop_size -
                 loop_size * ((n / loop_size) + 1);
            std::cout << n << " " << loop_size << std::endl;
        }

        if (!found_loop) cache[p] = n;

        tilt_north(p);
        tilt_west(p);
        tilt_south(p);
        tilt_east(p);
    }
}

int main() {
    std::fstream input("input.txt");

    platform p = parse(input);

    input.close();

    rotate(p, 1000'000'000);

    std::cout << calc_load(p) << std::endl;

    return 0;
}
