#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

typedef std::vector<std::pair<std::string, std::vector<int>>> springs;

std::unordered_map<std::string, int> cache;


springs parse(std::fstream& fs) {
    springs res;

    for (std::string line; std::getline(fs, line);) {
        std::vector<int> groups;
        std::string conditions;

        std::stringstream ss(line);

        ss >> conditions;
        for (std::string n; getline(ss, n, ',');)
            groups.push_back(std::stoi(n));

        res.emplace_back(conditions, groups);
    }

    return res;
}

void get_possible_rec(std::string cond, size_t pos,
                      std::unordered_set<std::string>& res) {
    size_t i;
    for (i = pos; i < cond.size(); i++) {
        if (cond[i] == '?') {
            cond[i] = '.';
            get_possible_rec(cond, i, res);
            cond[i] = '#';
            get_possible_rec(cond, i, res);
            break;
        }
    }

    if (i == cond.size()) res.insert(cond);
}

bool is_valid(std::string& str, std::vector<int>& groups) {
    size_t g_i = 0;
    size_t damaged_in_row = 0;

    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == '#') damaged_in_row++;

        if (str[i] == '.' && damaged_in_row > 0) {
            if (damaged_in_row != groups[g_i]) return false;

            damaged_in_row = 0;
            g_i++;
        }
    }

    return damaged_in_row == 0
               ? g_i >= groups.size()
               : damaged_in_row == groups[g_i] && g_i == groups.size() - 1;
}

long calc_arrangements(std::string cond, std::vector<int>& groups) {
    std::unordered_set<std::string> res;

    get_possible_rec(cond, 0, res);

    long n = 0;

    for (auto s : res) {
        if (is_valid(s, groups)) n++;
    }

    return n;
}

int main() {
    std::fstream input("input.txt");

    springs s = parse(input);

    input.close();

    long res = 0;
    for (auto& [cond, groups] : s) {
        res += calc_arrangements(cond, groups);
    }

    std::cout << res << std::endl;

    return 0;
}

