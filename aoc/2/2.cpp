#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>

// first part of the challenge
bool condition1(const std::string& pw, const char c, const uint32_t min, const uint32_t max)
{
    uint32_t cnt = std::count(pw.begin(), pw.end(), c);
    return (min <= cnt && cnt <= max);
}

// second part of the challenge
bool condition2(const std::string& pw, const char c, const uint32_t pos1, const uint32_t pos2)
{
    bool at_pos1;
    if (pos1 > pw.size())
        at_pos1 = false;
    else
        at_pos1 = pw.at(pos1 - 1) == c;

    bool at_pos2;
    if (pos2 > pw.size())
        at_pos2 = false;
    else
        at_pos2 = pw.at(pos2 - 1) == c;
    
    // xor-ing; only in one position
    return at_pos1 != at_pos2;
}

uint32_t check_pw(std::string path)
{
    std::ifstream infile(path);
    std::string minmax;
    std::string _c;
    std::string pw;
    
    uint32_t correct = 0;
    while (infile >> minmax >> _c >> pw) {
        // for the min max parsing
        uint32_t start = 0;
        uint32_t end = minmax.find("-");
        uint32_t min = std::stoi(minmax.substr(start, end));
        start = end + 1;
        uint32_t max = std::stoi(minmax.substr(start));

        char c = _c.at(0);
        if (condition2(pw, c, min, max))
            ++correct;
    }

    return correct;

}



int main()
{

    std::cout << "Number of correct paswords: " << check_pw("../aoc/2/input") << std::endl;
    
}