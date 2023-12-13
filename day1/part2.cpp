#include <ctype.h>

#include <fstream>
#include <iostream>
#include <map>

std::map<std::string, int> numbers{
    {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

int try_parse(std::string s) {
    if (isdigit(s[0])) return s[0] - 48;

    for (auto& [word, num] : numbers) {
        if (s.starts_with(word)) return num;
    }

    return -1;
}

int main() {
    std::ifstream file("input.txt");

    int first, last, res = 0;
    for (std::string line; getline(file, line);) {
        for (int i = 0; i <= line.size(); i++){
            if ((first = try_parse(line.c_str() + i)) != -1) break;
        }

        for (int i = line.size() - 1; i >= 0; i--){
            if ((last = try_parse(line.c_str() + i)) != -1) break;
        }

        res += first * 10 + last;
    }

    file.close();
    std::cout << res << std::endl;
    return 0;
}
