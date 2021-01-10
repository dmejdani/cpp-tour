#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Passport {

public:
    Passport(std::string& text) 
        : birth_year{-1}, issue_year{-1}, expiration_year{-1} 
        {fill_fields(text);};
    
    bool is_valid() const {
        return !( (birth_year == -1) || (issue_year == -1) || (expiration_year == -1) ||
                   height.empty() || hair_color.empty() || eye_color.empty() || passport_id.empty());                   
    }

    bool is_valid2() const {
        
        if (!is_valid()) return false;
        return (birth_year >= 1920 && birth_year <= 2002 &&
                issue_year >= 2010 && issue_year <= 2020 &&
                expiration_year >= 2020 && expiration_year <= 2030 &&
                valid_height() &&
                valid_hair_color() && 
                valid_eye_color() &&
                valid_passport_id());
    }

private:
    void fill_fields(std::string& text) {
        auto splitted = split(text, " ");
        parse_pairs(splitted);

    };

    std::vector<std::string> split(std::string& nonsplitted, const char* delimiter) const {
       std::vector<std::string> splitted;
        int32_t len = nonsplitted.find(delimiter);
            while (len != static_cast<int32_t>(std::string::npos)) {
                splitted.push_back(nonsplitted.substr(0, len));
                // Erase parsed part including the delimiter.
                nonsplitted.erase(0, len + 1);
                len = nonsplitted.find(" ");
            }
        return splitted;
    }

    void parse_pairs(std::vector<std::string>& splitted) {
        for (auto& sPair : splitted) {
            std::string key = sPair.substr(0, 3);
            std::string value = sPair.substr(4, std::string::npos);
            
            if      (key == "byr") { birth_year = std::stoi(value); }
            else if (key == "iyr") { issue_year = std::stoi(value); }
            else if (key == "eyr") { expiration_year = std::stoi(value); }
            else if (key == "hgt") { height = value; }
            else if (key == "hcl") { hair_color = value; }
            else if (key == "ecl") { eye_color = value; }
            else if (key == "pid") { passport_id = value; }
            else if (key == "cid") { country_id = value; }
            else std::cout << "unknown key" << std::endl;
        }
    }

    bool valid_height() const {
        std::string unit = height.substr(height.size() - 2, height.size());
        uint32_t value;
        try
        {
            value = std::stoi(height.substr(0, height.size() - 2));
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            return false;
        }
        if (unit == "cm") {
            return (value >= 150 && value <= 193);
        }
        else if (unit == "in") {
            return (value >= 59 && value <= 76);
        }
        return false;
    }

    bool valid_hair_color() const {
        if (hair_color[0] == '#' && hair_color.size() == 7) {
            try
            {
                // trying if the number is a valid hex number
                std::stoi(hair_color.substr(1, hair_color.size()), 0, 16);
                return true;
            }
            catch(const std::exception& e)
            {
                // std::cout << "hair wrong" << std::endl;
                // std::cerr << e.what() << '\n';
                return false;
            }
        }
        return false;
    }

    bool valid_eye_color() const {
        std::vector<std::string> colors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        return (std::find(colors.begin(), colors.end(), eye_color) != colors.end());
    }

    bool valid_passport_id() const {
        try
        {
            std::stoi(passport_id);
        }
        catch(const std::exception& e)
        {
            // std::cout << "passport id wrong" << std::endl;
            // std::cerr << e.what() << '\n';
            return false;
        }
        
        return passport_id.size() == 9;
    }

public:
    int32_t birth_year;
    int32_t issue_year;
    int32_t expiration_year;
    std::string height;
    std::string hair_color;
    std::string eye_color;
    std::string passport_id;
    std::string country_id;
};



std::vector<Passport> parse_input(std::string path) 
{
    std::vector<Passport> passports;

    std::ifstream input(path);
    std::string line;

    std::string text = "";
    while (std::getline(input, line)) {
        if (line != "") 
            text += line + " ";
        else {
            passports.emplace_back(std::move(Passport(text)));
            text = "";
        }
    }
    // ATTENTION: this is a bug source 😠
    // Get the last passport because that one is not separated by empty line.
    passports.emplace_back(std::move(Passport(text)));
    return passports;
}

int main() {
    int32_t valid_1 = 0, valid_2 = 0;
    std::vector<Passport> ps = parse_input("../aoc/4/input");
    for (auto& passport : ps) {
        if (passport.is_valid()) valid_1++;
        if (passport.is_valid2()) valid_2++;
    }

    std::cout << "Task 1: Number of valid passports: " << valid_1 << std::endl;
    std::cout << "Task 2: Number of valid passports: " << valid_2 << std::endl;
}
