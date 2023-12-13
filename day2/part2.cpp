#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::vector<std::string> split(std::string& s, char delim) {
    std::vector<std::string> res;
    std::stringstream ss(s);
    std::string token;

    while (getline(ss, token, delim)) {
        res.push_back(token);
    }

    return res;
}

std::map<std::string, int> minimum(std::string& s) {
    std::map<std::string, int> counter{{"red", 0}, {"green", 0}, {"blue", 0}};
    std::istringstream ss(s);
    std::string cubes, color;

    int number;

    while (getline(ss, cubes, ',')) {
        std::istringstream c(cubes);
        c >> std::ws >> number >> std::ws >> color;
        counter[color] = number;
    }

    return counter;
}

void combine(std::map<std::string, int>& m1, std::map<std::string, int> m2) {
    for (auto& [color, num] : m2) {
        m1.contains(color) ? m1[color] = std::max(num, m1[color])
                           : m1[color] = num;
    }
}

int main() {
    std::ifstream input{"input.txt"};

    int res = 0, id = 1;
    for (std::string line; std::getline(input, line); id++) {
        std::string game = line.substr(line.find(':') + 2, line.size());

        std::map<std::string, int> mins{};
        for (auto& round : split(game, ';')) {
            combine(mins, minimum(round));
        }

        int power = 1;
        for (auto& [_, num] : mins) {
            power *= num;
        }
        res += power;
    }

    input.close();
    std::cout << res << std::endl;
    return 0;
}
