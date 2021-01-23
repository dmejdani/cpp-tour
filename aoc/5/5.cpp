#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class BoardingPass {

public:
    BoardingPass(const std::string& seat)
        : row {-1}, col{-1} 
        { parseSeat(seat); };
    
    int32_t seatId() {
        return row * 8 + col;
    }

private:
    void parseSeat(const std::string& seat) {
        std::string s_row = seat.substr(0, 7);
        std::string s_col = seat.substr(7, seat.size());
        row = findRowCol(s_row);
        col = findRowCol(s_col);
    }

    int32_t findRowCol(const std::string& r) {
        int32_t row_col = 0;
        int32_t pos = r.size();
        for (const char& c : r) {
            switch (c)
            {
            case 'F':
                break;
            case 'B':
                row_col += 1 << (pos - 1);
            case 'L':
                break;
            case 'R':
                row_col += 1 << (pos - 1) ;
                break;
            default:
                throw std::runtime_error("non recognizable symbol '" + c + '\'');
                break;
            }
                
            pos -= 1;
        }

        return row_col;
    }

public:
    int32_t row;
    int32_t col;

};

std::vector<int32_t> getSeatIds(const std::string& path)
{
    std::vector<int32_t> sIds;

    std::ifstream input(path);
    std::string seat;
    while (input >> seat) {
        BoardingPass bp = BoardingPass(seat);
        sIds.push_back(bp.seatId());
    }

    return sIds;
}


int32_t findMissingSeat(std::vector<int32_t>& sIds)
{
    std::sort(sIds.begin(), sIds.end());
    for (uint32_t i = 0; i < (sIds.size() - 1); ++i) {
        int32_t diff = sIds[i + 1] - sIds[i];
        if (diff > 1)
            return sIds[i] + 1;
    }

    return -1;
}


int main()
{
    std::vector<int32_t> sIds = getSeatIds("../aoc/5/input");
    std::cout << "The maximum seat id is: " << *std::max_element(sIds.begin(), sIds.end()) << std::endl;
    std::cout << "The missing seat id is: " << findMissingSeat(sIds) << std::endl;
}