#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>


uint32_t cnt_trees(const std::string path, uint32_t right_step, uint32_t down_step)
{
    std::ifstream input;
    input.open(path);

    if (!input.is_open()) {
        perror("Error open"); 
        exit(EXIT_FAILURE);
    }

    uint32_t ver_pos = 0;
    uint32_t hor_pos = 0;

    uint32_t trees = 0;
    std::string line;
    while (getline(input, line))
    {
        if (!(ver_pos % down_step)) {
            
            if (line.at(hor_pos) == '#') 
                ++trees;
            
            hor_pos += right_step;
            hor_pos %= 31;
            
        }
        ++ver_pos;
    }

    return trees;
}


int main() 
{
    std::vector<std::pair<uint32_t, uint32_t>> vp_steps = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

    uint32_t prod = 1;
    for (const auto& pair: vp_steps) {
        auto right_step = pair.first;
        auto down_step = pair.second;

        prod *= cnt_trees("../aoc/3/input", right_step, down_step);
    }
    std::cout << "Product of trees: " << prod << std::endl;

} 