#include <ctype.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

typedef std::vector<std::vector<std::tuple<long long, long long, long long>>>
    almanach;

std::vector<long long> get_seeds(std::fstream& fs) {
    std::vector<long long> res;

    std::string _;
    fs >> _;

    long long seed;
    while (fs >> seed) {
        res.push_back(seed);
    }

    fs.clear();

    return res;
}

almanach get_almanach(std::fstream& fs) {
    almanach res;

    long long dst, src, range;
    std::vector<std::tuple<long long, long long, long long>> map;
    for (std::string line; std::getline(fs, line);) {
        if (isdigit(line[0])) {
            sscanf(line.c_str(), "%lld %lld %lld", &dst, &src, &range);
            map.emplace_back(dst, src, range);
        }

        else if (!map.empty()) {
            res.push_back(map);
            map.clear();
        }
    }
    res.push_back(map);

    return res;
}

long long calculate_location(long long seed, almanach& al) {
    for (auto& map : al) {
        for (auto& [dst, src, range] : map) {
            if (seed >= src && seed < src + range) {
                seed += dst - src;
                break;
            }
        }
    }

    return seed;
}

int main() {
    std::fstream input("input.txt");
    std::string line;

    std::vector<long long> seeds = get_seeds(input);
    for (long long s : seeds) {
        std::cout << s << std::endl;
    }
    almanach al = get_almanach(input);

    std::for_each(seeds.begin(), seeds.end(),
                  [&](long long& s) { s = calculate_location(s, al); });

    std::cout << *std::min_element(seeds.begin(), seeds.end()) << std::endl;

    input.close();
    return 0;
}
