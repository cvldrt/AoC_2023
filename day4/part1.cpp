#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

void parse_nums(std::string s, std::set<int>& set) {
    int n;
    std::istringstream ss(s);

    while (ss >> std::ws >> n) {
        set.emplace(n);
    }
}

int main() {
    std::fstream input("input.txt");

    int res = 0, points, game_n = 1;
    for (std::string line; std::getline(input, line); game_n++) {
        size_t sc = std::find(line.begin(), line.end(), ':') - line.begin();
        size_t p = std::find(line.begin(), line.end(), '|') - line.begin();

        std::set<int> my_nums, winning_nums;
        std::vector<int> intersection;

        parse_nums(line.substr(sc + 1, p - sc - 2), winning_nums);
        parse_nums(line.substr(p + 1, line.size() - p), my_nums);

        std::set_intersection(my_nums.begin(), my_nums.end(),
                              winning_nums.begin(), winning_nums.end(),
                              std::back_inserter(intersection));

        res += intersection.size() == 0 ? 0 : std::pow(2, intersection.size() - 1);

    }

    input.close();
    std::cout << res << std::endl;
    return 0;
}
