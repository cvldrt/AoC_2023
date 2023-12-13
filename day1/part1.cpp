#include <ctype.h>

#include <algorithm>
#include <fstream>
#include <iostream>

constexpr auto is_digit = [](char c) { return isdigit(c); };

int main() {
    std::ifstream input("input.txt");

    int res = 0;
    for (std::string line; getline(input, line);) {
        int first = *std::find_if(line.begin(), line.end(), is_digit) - 48;
        int last =
            std::ranges::find_last_if(line.begin(), line.end(), is_digit)[0] -
            48;

        res += first * 10 + last;
    }

    input.close();

    std::cout << res << std::endl;
    return 0;
}
