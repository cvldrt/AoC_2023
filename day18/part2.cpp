#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

typedef int64_t i64;
typedef std::pair<i64, i64> coor;
typedef std::map<coor, coor> lagoon;

i64 parse_input(lagoon& l, std::fstream& fs) {
    coor current = {0, 0};
    i64 res = 0;

    for (std::string line; std::getline(fs, line);) {
        char _ch;
        int _int;
        std::string hex;

        std::stringstream ss(line);

        ss >> _ch >> std::ws >> _int >> hex;
        hex.erase(0, 2);

        char direction = hex[hex.size() - 2];
        hex.erase(hex.size() - 2);

        i64 distance = std::stol(hex, nullptr, 16);

        res += distance;

        switch (direction) {
            case '3':
                l[current] = {current.first, current.second + distance};
                current = {current.first, current.second + distance};
                break;
            case '1':
                l[current] = {current.first, current.second - distance};
                current = {current.first, current.second - distance};
                break;
            case '2':
                l[current] = {current.first - distance, current.second};
                current = {current.first - distance, current.second};
                break;
            case '0':
                l[current] = {current.first + distance, current.second};
                current = {current.first + distance, current.second};
                break;
        }
    }

    return res;
}

i64 shoelace(lagoon& l) {
    i64 leftSum = 0;
    i64 rightSum = 0;

    for (auto& [c1, c2] : l) {
        leftSum += c1.first * c2.second;
        rightSum += c2.first * c1.second;
    }

    return 0.5 * std::abs(leftSum - rightSum);
}

int main() {
    std::fstream input("input.txt");

    lagoon l;
    i64 perimeter = parse_input(l, input);

    input.close();

    std::cout << shoelace(l) + perimeter / 2 + 1 << std::endl;

    return 0;
}
