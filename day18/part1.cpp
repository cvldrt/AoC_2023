#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

typedef std::pair<int, int> coor;
typedef std::map<coor, coor> lagoon;

int parse_input(lagoon& l, std::fstream& fs) {
    coor current = {0, 0};
    int res = 0;

    for (std::string line; std::getline(fs, line);) {
        char direction;
        int distance;

        std::stringstream ss(line);

        ss >> direction >> std::ws >> distance;

        res += distance;

        switch (direction) {
            case 'U':
                l[current] = {current.first, current.second + distance};
                current = {current.first, current.second + distance};
                break;
            case 'D':
                l[current] = {current.first, current.second - distance};
                current = {current.first, current.second - distance};
                break;
            case 'L':
                l[current] = {current.first - distance, current.second};
                current = {current.first - distance, current.second};
                break;
            case 'R':
                l[current] = {current.first + distance, current.second};
                current = {current.first + distance, current.second};
                break;
        }
    }

    return res;
}

int shoelace(lagoon& l) {
    int leftSum = 0;
    int rightSum = 0;

    for (auto& [c1, c2] : l) {
        leftSum += c1.first * c2.second;
        rightSum += c2.first * c1.second;
    }

    return 0.5 * abs(leftSum - rightSum);
}

int main() {
    std::fstream input("input.txt");

    lagoon l;
    int perimeter = parse_input(l, input);

    input.close();

    std::cout << shoelace(l) + perimeter / 2 + 1 << std::endl;

    return 0;
}
