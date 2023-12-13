#include <ctype.h>

#include <fstream>
#include <iostream>
#include <vector>

typedef std::vector<std::string> engine_shematic;

size_t find_first_digit(std::string& s, size_t pos) {
    while (isdigit(s[pos - 1]) && pos-- > 0) {
    }
    return pos;
}

void erase_num(std::string& s, size_t pos) {
    if (s[pos] == '.') return;
    pos = find_first_digit(s, pos);

    while (isdigit(s[pos]) && pos < s.size()) {
        s[pos++] = '.';
    }
}

int read_num(std::string& s, size_t pos) {
    if (s[pos] == '.') return 0;

    pos = find_first_digit(s, pos);

    int res = 0;
    while (isdigit(s[pos]) && pos < s.size()) {
        res = res * 10 + s[pos++] - 48;
    }

    return res;
}

int sum_around(engine_shematic& es, int x_i, int y_i) {
    int res = 1;
    int found = 0;
    for (int y = -1; y < 2; y++) {
        for (int x = -1; x < 2; x++) {
            if (y_i + y >= 0 && y_i + y < es.size() &&
                x_i + x >= 0 && x_i + x < es[y_i + y].size()) {
                int num =  read_num(es[y_i + y], x_i + x);

                if (num > 0){
                    found++;
                    res *= num;
                }

                erase_num(es[y_i + y], x_i + x);
            }
        }
    }
    return found == 2 ? res : 0;
}

int main() {
    std::ifstream input("input.txt");

    engine_shematic es;

    for (std::string line; std::getline(input, line);) {
        es.push_back(line);
    }

    int res = 0;
    for (int y = 0; y < es.size(); y++)
        for (int x = 0; x < es[y].size(); x++)
            if (!std::isdigit(es[y][x]) && es[y][x] != '.') {
                int sum = sum_around(es, x, y);
                res += sum;
                std::cout << sum << std::endl;
            }

    std::cout << res << std::endl;
}
