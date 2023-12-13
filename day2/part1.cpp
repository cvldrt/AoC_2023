#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::map<std::string, int> limits{{"red", 12}, {"green", 13}, {"blue", 14}};

std::vector<std::string> split(std::string& s, char delim) {
    std::vector<std::string> res;
    std::stringstream ss(s);
    std::string token;

    while (getline(ss, token, delim)) {
        res.push_back(token);
    }

    return res;
}

bool is_valid(std::string& s) {
    std::stringstream ss(s);
    std::string cubes, color;
    int number;

    while (getline(ss, cubes, ',')) {
        std::istringstream c(cubes);
        c >> std::ws >> number >> std::ws >> color;
        if (limits[color] < number) return false;
    }

    return true;
}

int main() {
    std::ifstream input{"input.txt"};

    int res = 0, id = 1;
    for (std::string line; std::getline(input, line); id++) {
        std::string game = line.substr(line.find(':') + 2, line.size());

        bool valid = true;
        for (auto& round : split(game, ';')) {
            if (!is_valid(round)) {
                valid = false;
                break;
            }
        }

        if (valid) res += id;
    }

    input.close();
    std::cout << res << std::endl;
    return 0;
}
