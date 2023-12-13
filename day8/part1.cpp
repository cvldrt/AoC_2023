#include <fstream>
#include <iostream>
#include <map>

typedef std::map<std::string, std::pair<std::string, std::string>> network;

void load_network(std::fstream& fs, network& n){

    char start[4], left[4], right[4];

    for (std::string line; getline(fs, line);){
        sscanf(line.c_str(), "%3s%*4c%3s%*2c%3s", start, left, right);
        n[start] = {left, right};
    }
}

int main(){
    std::fstream input("input.txt");

    network n;

    std::string directions;
    input >> directions >> std::ws;

    load_network(input, n);

    input.close();

    std::string current = "AAA";
    int i = 0, steps = 0;

    while (current != "ZZZ"){
        current = directions[i++] == 'L' ? n[current].first : n[current].second;
        steps++;
        
        if (i == directions.size()) i = 0;
    }

    std::cout << steps << std::endl;

    return 0;
}
