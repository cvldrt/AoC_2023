#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

std::vector<std::vector<int>> read_nums(std::fstream& fs) {
    std::vector<std::vector<int>> res;

    int num;
    for (std::string line; std::getline(fs, line);) {
        std::vector<int> lvec;

        std::istringstream ss(line);

        while (ss >> num) lvec.push_back(num);

        res.push_back(lvec);
    }

    return {res};
}

bool zeros(std::vector<int>& vec, int index) {
    for (int i = 0; i <= index; i++) {
        if (vec[i] != 0) return false;
    }
    return true;
}

int calculate_next(std::vector<int>& vec) {
    int max_i = vec.size() - 1;

    while (!zeros(vec, max_i)) {
        for (int i = 0; i < max_i; i++) {
            vec[i] = vec[i + 1] - vec[i];
        }
        max_i--;
    }

    return std::accumulate(vec.begin(), vec.end(), 0);
}

int main() {
    std::fstream input("input.txt");

    int res = 0;
    for (std::vector<int>& vec : read_nums(input)) {
        std::reverse(vec.begin(), vec.end());
        res += calculate_next(vec);
    }

    input.close();

    std::cout << res << std::endl;

    return 0;
}
