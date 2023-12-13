#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

long calc_distance(long time, long charge) { return charge * (time - charge); }

long read_nums(std::fstream& fs) {
    long res = 0;

    std::string _;
    fs >> _;

    long num;
    while (fs >> num)
        res = res * std::pow(10, std::to_string(num).size()) + num;

    fs.clear();

    return res;
}

int main() {
    std::fstream input("input.txt");

    long time = read_nums(input);
    long distance = read_nums(input);

    std::cout << time << std::endl;
    std::cout << distance << std::endl;

    input.close();

    long res = 0;

    for (long t = 0; t <= time; t++) {
        if (calc_distance(time, t) > distance) {
            res++;
        }
    }

    std::cout << res << std::endl;

    return 0;
}
