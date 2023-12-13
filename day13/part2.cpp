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

int comp(std::vector<std::string>& pat, int col1, int col2, bool ver) {
    int wrong = 0;

    if (!ver) {
        for (int i = 0; i < pat[0].size(); i++) {
            if (pat[col1][i] != pat[col2][i]) wrong++;
        }

    } else {
        for (auto row : pat) {
            if (row[col1] != row[col2]) wrong++;
        }
    }

    return wrong;
}

int check_reflection(std::vector<std::string>& pat, int start, bool ver,
                     bool err) {
    int wrong, x = 0;

    while ((wrong = comp(pat, start + x + 1, start - x, ver)) == 0 ||
           !err && wrong == 1) {
        if (wrong == 1) {
            err = true;
        }

        if (!ver && start + x + 1 >= pat.size() - 1 ||
            ver && start + x + 1 >= pat[0].size() - 1 || start - x <= 0) {
            return err ? start + 1 : 0;
        }
        x++;
    }

    return 0;
}

uint64_t reflections(std::vector<std::string>& pat) {
    uint64_t res = 0;

    for (int row = 0; row < pat.size(); row++) {
        if (row < pat.size() - 1) {
            if (comp(pat, row, row + 1, false) < 2) {
                res += check_reflection(pat, row, false, false) * 100;
            }
        }
    }

    for (int col = 0; col < pat[0].size(); col++) {
        if (col < pat[0].size() - 1) {
            if (comp(pat, col, col + 1, true) < 2) {
                res += check_reflection(pat, col, true, false);
            }
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
