#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class BoardingPass
{

public:
    BoardingPass(const std::string &seat)
        : row{-1}, col{-1}
    {
        parseSeat(seat);
    };

    int32_t seatId()
    {
        return row * 8 + col;
    }

private:
    void parseSeat(const std::string &seat)
    {
        std::string s_row = seat.substr(0, 7);
        std::string s_col = seat.substr(7, seat.size());
        row = findRowCol(s_row);
        col = findRowCol(s_col);
    }

    int32_t findRowCol(const std::string &r)
    {
        int32_t row_col = 0;
        int32_t pos = r.size();
        for (const char &c : r)
        {
            switch (c)
            {
            case 'F':
                break;
            case 'B':
                row_col += 1 << (pos - 1);
            case 'L':
                break;
            case 'R':
                row_col += 1 << (pos - 1);
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

int32_t getMaxSeatId(const std::string &path)
{
    std::vector<int32_t> sIds;

    std::ifstream input(path);
    std::string seat;
    while (input >> seat)
    {
        BoardingPass bp = BoardingPass(seat);
        sIds.push_back(bp.seatId());
    }

    return *std::max_element(sIds.begin(), sIds.end());
}

int main()
{
    std::cout << getMaxSeatId("../aoc/5/input") << std::endl;
}