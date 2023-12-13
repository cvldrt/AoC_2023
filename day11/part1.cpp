#include <fstream>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::string> load_image(std::fstream& fs) {
    std::vector<std::string> res;

    for (std::string line; std::getline(fs, line);) res.push_back(line);

    return res;
}

void expand(std::vector<std::string>& img) {
    for (auto it = img.begin(); it < img.end(); it++) {
        if (!(*it).contains('#')) {
            img.insert(++it, *it);
        }
    }

    bool has_galaxies;
    std::vector<size_t> to_expand;
    for (int x = 0; x < img[0].size(); x++) {
        has_galaxies = false;

        for (int y = 0; y < img.size(); y++) {
            if (img[y][x] == '#') {
                has_galaxies = true;
                break;
            }
        }

        if (!has_galaxies) to_expand.push_back(x);
    }

    for (auto& line : img) {
        for (int i = 0; i < to_expand.size(); i++) {
            line.insert(to_expand[i] + i, ".");
        }
    }
}

std::set<std::pair<int, int>> get_galaxies(std::vector<std::string>& img) {
    std::set<std::pair<int, int>> res;
        
    for (int y = 0; y < img.size(); y++){
        for (int x = 0; x < img[y].size(); x++){
            if (img[y][x] == '#') res.emplace(x, y);
        }
    }

    return res;
}

int main() {
    std::fstream input("input.txt");

    auto image = load_image(input);

    input.close();

    expand(image);

    auto gal_coords = get_galaxies(image);

    int res = 0;

    for (auto [x1, y1]: gal_coords){
        for (auto [x2, y2]: gal_coords){
            res += abs(x1 - x2) + abs(y1 - y2);
        }
    }

    res /= 2;

    std::cout << res << std::endl;

    return 0;
}
