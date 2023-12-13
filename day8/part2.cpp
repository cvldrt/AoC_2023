#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

typedef std::map<std::string, std::pair<std::string, std::string>> network;

void load_network(std::fstream& fs, network& n) {
    char start[4], left[4], right[4];

    for (std::string line; getline(fs, line);) {
        sscanf(line.c_str(), "%3s%*4c%3s%*2c%3s", start, left, right);
        n[start] = {left, right};
    }
}

std::vector<std::string> get_starts(network& n) {
    std::vector<std::string> res;
    for (auto& [key, _] : n) {
        if (key[2] == 'A') res.push_back(key);
    }
    return res;
}

bool in_finish(std::vector<std::string>& vec) {
    for (auto s : vec)
        if (s[2] != 'Z') return false;

    return true;
}

int main() {
    std::fstream input("input.txt");

    network n;

    std::string directions;
    input >> directions >> std::ws;

    load_network(input, n);

    input.close();

    std::vector<int> steps;

    for (auto& str : get_starts(n)){
        std::string current = str;
        int i = 0, s = 0;

        while (current[2] != 'Z'){
            current = directions[i++] == 'L' ? n[current].first : n[current].second;
            s++;
            
            if (i == directions.size()) i = 0;
        }

        steps.push_back(s);
    }

    uint64_t res = 1;
    for (int i : steps){
        std::cout << i << std::endl;
        res = std::lcm(res, i);
    }

    std::cout << res << std::endl;

    return 0;
}
