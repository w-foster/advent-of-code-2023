#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

#include "json.hpp"

using json = nlohmann::json;


int main() {

    // Setting up a vector<string> with the lines
    std::ifstream f("day3_lines.json");
    if (!f.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return 1;
    }

    json data;
    f >> data;

    std::vector<std::string> lines = data.get<std::vector<std::string>>();
    
    size_t line_size = lines[0].size();
    std::string filler_line(line_size, '.');
    lines.push_back(filler_line);
    lines.insert(lines.begin(), filler_line);

    for (auto &line : lines) {
        line.push_back('.');
        line.insert(line.begin(), '.');
        //std::cout << line << "\n";
    }

    size_t vec_size = lines.size();
    line_size = lines[0].size();
    int sum_of_part_nums = 0;
    // Ignore first and last lines (the filler lines)
    for (int line_idx = 1; line_idx < vec_size - 1; line_idx++) {
        std::string line = lines[line_idx];
        std::cout << line << "\n";
        int char_idx = 1; // ignore first char (filler char '.')
        while (char_idx < line_size - 1 /* ignore last char */) {
            if (!isdigit(line[char_idx])) {
                char_idx++;
                continue;
            }
            int curr_digit_idx = char_idx;
            std::string digits;
            bool is_part_number = false;
            while (isdigit(line[curr_digit_idx])) {
                // If num not yet confirmed as part number, search for symbols
                if (!is_part_number) {
                    std::vector<char> adjacent_chars;
                    std::string prev_line = lines[line_idx - 1];
                    std::string next_line = lines[line_idx + 1];
                    adjacent_chars.insert(adjacent_chars.end(), {
                        line[curr_digit_idx - 1],
                        line[curr_digit_idx + 1],
                        prev_line[curr_digit_idx - 1],
                        prev_line[curr_digit_idx],
                        prev_line[curr_digit_idx + 1],
                        next_line[curr_digit_idx - 1],
                        next_line[curr_digit_idx],
                        next_line[curr_digit_idx + 1]
                    });
                    for (const char &ch : adjacent_chars) {
                        if (!isdigit(ch) && ch != '.' && ch != '.') {
                            is_part_number = true;
                            break;
                        }
                    }
                }
                digits.push_back(line[curr_digit_idx]);
                curr_digit_idx++;
            }
            
            
            int num = std::stoi(digits);
            std::cout << "Found num: " << num << "\n";
            if (is_part_number) {
                std::cout << "IS PART NUM" << "\n";
                sum_of_part_nums += num;
                std::cout << "New sum: " << sum_of_part_nums << "\n";
            }
            char_idx += curr_digit_idx - char_idx;
        }
    }

    std::cout << sum_of_part_nums << "\n";

    return 0;
}

// ANSWER: 520019