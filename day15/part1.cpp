#include <cstdint>
#include <fstream>
#include <iostream>

int main(){
    std::fstream input("input.txt");

    uint64_t res = 0, curr_val;
    for (std::string line; std::getline(input, line, ',');){

        curr_val = 0;

        for (char ch : line){
            if (ch == '\n') continue;
            curr_val += ch;
            curr_val *= 17;
            curr_val %= 256;
        }

        res += curr_val;
    }

    input.close();

    std::cout << res << std::endl;

    return 0;
}
