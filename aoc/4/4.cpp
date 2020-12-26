#include <fstream>
#include <string>
#include <iostream>
#include <vector>


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
            passports.push_back(std::move(Passport(text)));
            text = "";
            return passports;
        }
    }
}


class Passport {

public:
    Passport(std::string& text) 
        : birth_year{-1}, issue_year{-1}, expiration_year{-1} 
        {fill_fields(text);}
private:
    void fill_fields(std::string& text) {
        auto splitted = split(text, " ");
        parse_pairs(splitted);

    };

    std::vector<std::string> split(std::string& nonsplitted, const char* delimiter) {
       std::vector<std::string> splitted;
        int32_t len = nonsplitted.find(delimiter);
            while (len != std::string::npos) {
                splitted.push_back(nonsplitted.substr(0, len));
                // Erase parsed part including the delimiter.
                nonsplitted.erase(0, len + 1);
                len = nonsplitted.find(" ");
            }
        return std::move(splitted);
    }

    void parse_pairs(std::vector<std::string>& splitted) {
        for (auto& sPair : splitted) {
            std::string key = sPair.substr(0, 3);
            std::string value = sPair.substr(4, std::string::npos);
            
            if (key == "byr") { birth_year = std::stoi(value); }
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

    int32_t birth_year;
    int32_t issue_year;
    int32_t expiration_year;
    std::string height;
    std::string hair_color;
    std::string eye_color;
    std::string passport_id;
    std::string country_id;
};

int main() {
    std::vector<Passport> ps = parse_input("../aoc/4/input");
}