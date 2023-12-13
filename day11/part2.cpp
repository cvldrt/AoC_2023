#include <fstream>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::string> load_image(std::fstream& fs) {
    std::vector<std::string> res;

    for (std::string line; std::getline(fs, line);) res.push_back(line);

    return res;
}

std::pair<std::vector<int>, std::vector<int>> expand(
    std::vector<std::string>& img) {
    std::vector<int> to_expand_vertical;

    for (auto it = img.begin(); it < img.end(); it++) {
        if (!(*it).contains('#')) {
            to_expand_vertical.push_back(it - img.begin());
        }
    }

    bool has_galaxies;
    std::vector<int> to_expand_horizontal;
    for (int x = 0; x < img[0].size(); x++) {
        has_galaxies = false;

        for (int y = 0; y < img.size(); y++) {
            if (img[y][x] == '#') {
                has_galaxies = true;
                break;
            }
        }

        if (!has_galaxies) to_expand_horizontal.push_back(x);
    }

    return {to_expand_vertical, to_expand_horizontal};
}

std::set<std::pair<int, int>> get_galaxies(std::vector<std::string>& img) {
    std::set<std::pair<int, int>> res;

    for (int y = 0; y < img.size(); y++) {
        for (int x = 0; x < img[y].size(); x++) {
            if (img[y][x] == '#') res.emplace(x, y);
        }
    }

    return res;
}

inline bool between(int a, int x1, int x2){
    return x1 < a && x2 > a || x2 < a && x1 > a;
}

int main() {
    std::fstream input("input.txt");

    auto image = load_image(input);

    input.close();

    auto [vertical, horizontal] = expand(image);

    auto gal_coords = get_galaxies(image);

    long res = 0;

    for (auto [x1, y1] : gal_coords) {
        for (auto [x2, y2] : gal_coords) {
            res += abs(x1 - x2) + abs(y1 - y2);

            for (int row : vertical) {
                if (between(row, y1, y2)) res += 999999;
            }

            for (int col : horizontal) {
                if (between(col, x1, x2)) res += 999999;
            }
        }
    }

    res /= 2;

    std::cout << res << std::endl;

    return 0;
}
