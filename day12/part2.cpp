#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

typedef std::vector<std::pair<std::string, std::vector<int>>> springs;
typedef std::tuple<int, int> pair;

struct pair_hash {
    template <class T1, class T2, class T3>
    std::size_t operator()(const std::tuple<T1, T2, T3>& t) const {
        auto [e1, e2, e3] = t;
        return std::hash<T1>()(e1) ^ std::hash<T2>()(e2) ^ std::hash<T2>()(e3);
    }
};

std::unordered_map<std::tuple<int, int, int>, uint64_t, pair_hash> cache;

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

uint64_t calc_rec(std::string& str, std::vector<int>& groups, size_t pos, long g_i,
              long cur_group) {

    if (cache.contains({pos, cur_group, g_i})) {
        return cache[{pos, cur_group, g_i}];
    }

    if (str.size() == pos) {
        if (cur_group == 0 && g_i == groups.size())
            return 1;

        else if (g_i == groups.size() - 1 && cur_group == groups[g_i])
            return 1;

        else
            return 0;
    }

    uint64_t res = 0;

    if (str[pos] == '#' || str[pos] == '?') {
        res += calc_rec(str, groups, pos + 1, g_i, cur_group + 1);
    }

    if (str[pos] == '.' || str[pos] == '?') {
        if (cur_group == 0) {
            res += calc_rec(str, groups, pos + 1, g_i, 0);
        } else if (g_i < groups.size() && groups[g_i] == cur_group) {
            res += calc_rec(str, groups, pos + 1, g_i + 1, 0);
        }
    }

    cache[{pos, cur_group, g_i}] = res;

    return res;
}

uint64_t calc(std::string str, std::vector<int>& groups) {
    cache = {};
    return calc_rec(str, groups, 0,  0, 0);
}

void multiply(std::vector<int>& t, size_t n) {
    auto t_copy = t;
    for (int i = 0; i < n - 1; i++) {
        t.insert(t.end(), t_copy.begin(), t_copy.end());
    }
}

void multiply(std::string& t, size_t n) {
    auto t_copy = t;
    for (int i = 0; i < n - 1; i++) {
        t.append("?");
        t.append(t_copy);
    }
}

int main() {
    std::fstream input("input.txt");

    springs s = parse(input);

    input.close();

    uint64_t res = 0;
    for (auto& [cond, groups] : s) {

        int n = 5;
        multiply(cond, n);
        multiply(groups, n);

        res += calc(cond, groups);
    }

    std::cout << res << std::endl;

    return 0;
}
