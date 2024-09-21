#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include "json.hpp"

using json = nlohmann::json;

int main() {

    // Setting up a vector<string> with the lines
    std::ifstream f("day1_lines_v2.json");
    if (!f.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return 1;
    }

    json data;
    f >> data;

    std::vector<std::string> lines_final = data.get<std::vector<std::string>>();
    
    
    for (auto line : lines_final) {
        std::cout << line << "\n";
    }
    

    // Iterating through the lines, getting the calibration value for each one
    int sum_of_calibration_values = 0;
    for (const std::string &line : lines_final) {
        std::cout << line << "\n";
        int calibration_value_1 = -1, 
            calibration_value_2 = -1;
        // Search for first char that represents a digit, starting from index 0
        int char_index = 0;
        int line_size = line.size();
        while (calibration_value_1 == -1 && char_index < line_size) {
            if (std::isdigit(line[char_index])) {
                // This assigns the int amount because in ASCII '0' = 48 and the ints are sequentially ordered
                // so e.g. '2' = 50, so 50 - 48 = 2 (the int)
                calibration_value_1 = line[char_index] - '0';
                std::cout << calibration_value_1 << " ";
            }
            char_index++;
        }
        char_index = line_size - 1;
        while (calibration_value_2 == -1 && char_index >= 0) {
            if (std::isdigit(line[char_index])) {
                calibration_value_2 = line[char_index] - '0';
                std::cout << calibration_value_2 << " ";
            }
            char_index--;
        }
        // Add the final cal value, e.g., for '7', '4', its 74
        std::cout << "\n" << sum_of_calibration_values;
        sum_of_calibration_values += calibration_value_1 * 10 + calibration_value_2;
        std::cout << " -> " << sum_of_calibration_values << std::endl;
    }
    
    std::cout << sum_of_calibration_values << std::endl;

    return 0;
}