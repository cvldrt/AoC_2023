#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<std::string>> island;

island parse(std::fstream& fs) {
    island res;

    std::vector<std::string> patterns;

    for (std::string line; std::getline(fs, line);) {
        if (line.empty()) {
            res.push_back(patterns);
            patterns = {};
            continue;
        }

        patterns.push_back(line);
    }

    res.push_back(patterns);

    return res;
}

bool comp(std::vector<std::string>& pat, int col1, int col2, bool ver) {
    if (!ver) {
        return pat[col1] == pat[col2];
    }

    for (auto row : pat) {
        if (row[col1] != row[col2]) return false;
    }

    return true;
}

int check_reflection(std::vector<std::string>& pat, int start, bool ver) {
    int x = 0;

    while (comp(pat, start + x + 1, start - x, ver)) {
        if (!ver && start + x + 1 >= pat.size() - 1 ||
            ver && start + x + 1 >= pat[0].size() - 1 || start - x <= 0) {
            return start + 1;
        }
        x++;
    }

    return 0;
}

uint64_t reflections(std::vector<std::string>& pat) {
    uint64_t res = 0;

    for (int row = 0; row < pat.size(); row++) {
        if (row < pat.size() - 1 && comp(pat, row, row + 1, false)) {
            res += check_reflection(pat, row, false) * 100;
        }
    }

    for (int col = 0; col < pat[0].size(); col++) {
        if (col < pat[0].size() - 1 && comp(pat, col, col + 1, true)) {
            res += check_reflection(pat, col, true);
        }
    }

    return res;
}

int main() {
    std::fstream input("input.txt");

    island is = parse(input);

    input.close();

    uint64_t res = 0;
    int i = 0;

    for (auto pattern : is) {
        res += reflections(pattern);
    }

    std::cout << res << std::endl;

    return 0;
}
