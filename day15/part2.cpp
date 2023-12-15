#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<int, std::vector<std::pair<std::string, int>>>
    hashmap;

void hashmap_insert(hashmap& hm, int hash, std::string&& label,
                    int focal_length) {
    if (!hm.contains(hash)) {
        hm[hash] = {{label, focal_length}};
        return;
    }

    auto it = std::find_if(hm[hash].begin(), hm[hash].end(),
                           [&](auto p) { return p.first == label; });

    if (it == hm[hash].end())
        hm[hash].push_back({label, focal_length});
    else
        *it = {label, focal_length};
}

void hashmap_remove(hashmap& hm, int hash, std::string&& label) {
    if (!hm.contains(hash)) {
        return;
    }

    std::erase_if(hm[hash], [label](auto p) { return p.first == label; });
}

void load_hashmap(hashmap& hm, std::fstream& fs) {
    uint64_t res = 0, curr_val;

    for (std::string line; std::getline(fs, line, ',');) {
        curr_val = 0;

        for (int i = 0; i < line.size(); i++) {
            switch (line[i]) {
                case '=':
                    hashmap_insert(hm, curr_val, line.substr(0, i),
                                   line[i + 1] - 48);
                    break;
                case '-':
                    hashmap_remove(hm, curr_val, line.substr(0, i));
                    break;
            }

            curr_val += line[i];
            curr_val *= 17;
            curr_val %= 256;
        }
    }
}

uint64_t calc_power(hashmap& hm) {
    uint64_t res = 0;
    for (int hash = 0; hash < 256; hash++) {
        if (!hm.contains(hash)) continue;

        for (int slot = 0; slot < hm[hash].size(); slot++) {
            res += (hash + 1) * (slot + 1) * hm[hash][slot].second;
        }
    }

    return res;
}

int main() {
    hashmap hm;
    std::fstream input("input.txt");

    load_hashmap(hm, input);

    input.close();

    std::cout << calc_power(hm) << std::endl;

    return 0;
}
