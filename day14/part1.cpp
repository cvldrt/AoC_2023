#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

typedef std::vector<std::string> platform;

platform parse(std::fstream& fs) {
    platform res;

    for (std::string line; std::getline(fs, line);) {
        res.push_back(line);
    }

    return res;
}

void tilt(platform& p) {
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

uint64_t calc_load(platform& p) {
    uint64_t res = 0;
    int m = p.size();

    for (auto line : p) {
        res += std::count(line.begin(), line.end(), 'O') * m--;
    }

    return res;
}

int main() {
    std::fstream input("input.txt");

    platform p = parse(input);

    input.close();

    tilt(p);

    std::cout << calc_load(p) << std::endl;

    return 0;
}
