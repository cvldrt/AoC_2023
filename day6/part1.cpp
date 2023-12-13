#include <fstream>
#include <iostream>
#include <vector>

int distance(int time, int charge) { return charge * (time - charge); }

std::vector<int> read_nums(std::fstream& fs) {
    std::vector<int> res;

    std::string _;
    fs >> _;

    int num;
    while (fs >> num) res.push_back(num);

    fs.clear();

    return res;
}

int main() {
    std::fstream input("input.txt");

    std::vector<int> times = read_nums(input);
    std::vector<int> distances = read_nums(input);

    input.close();

    int times_won = 0, res = 1;

    for (int i = 0; i < times.size(); i++) {
        for (int t = 0; t <= times[i]; t++) {
            if (distance(times[i], t) > distances[i]) {
                times_won++;
            }
        }
        res *= times_won;
        times_won = 0;
    }

    std::cout << res << std::endl;

    return 0;
}
