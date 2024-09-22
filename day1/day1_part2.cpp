#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include <algorithm>

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
    
    /*
    for (auto line : lines_final) {
        std::cout << line << "\n";
    }
    */
   
    std::unordered_map<std::string, char> string_num_map = {
        {"one", '1'},
        {"two", '2'},
        {"three", '3'},
        {"four", '4'},
        {"five", '5'},
        {"six", '6'},
        {"seven", '7'},
        {"eight", '8'},
        {"nine", '9'}
    };

    // Iterating through the lines, getting the calibration value for each one
    int sum_of_calibration_values = 0;
    for (const std::string &line : lines_final) {
        std::cout << "\n" << line << "\n";
        int calibration_value_1 = -1, 
            calibration_value_2 = -1;
        
        int char_index = 0;
        size_t line_size = line.size();
        while (calibration_value_1 == -1 && char_index < line_size) {
            // FIRST: check if the char by itself is a digit
            if (std::isdigit(line[char_index])) {
                // This assigns the int amount because in ASCII '0' = 48 and the ints are sequentially ordered
                // so e.g. '2' = 50, so 50 - 48 = 2 (the int)
                calibration_value_1 = line[char_index] - '0';
            } // SECOND: (if not digit) check if the char forms the first char in a substring that represents a num (e.g. 'four')
            else {
                // Loop through every key/value pair in the string:num map
                for (const auto &pair : string_num_map) {
                    int key_char_index = 0; // current index in the key string
                    int char_index_copy = char_index;
                    size_t key_size = pair.first.size();
                    // First check if there is no space left in the line to fit the key
                    if (line_size - char_index < key_size) {
                        continue;
                    }
                    // If space, loop thru each char in the key and compare it to the chars in the line
                    bool matched = true; // assume that a match has been found, for potential counterexample
                    while (key_char_index < key_size && matched) {
                        if (pair.first[key_char_index] != line[char_index_copy]) {
                            matched = false;
                        }
                        key_char_index++;
                        char_index_copy++;
                    }
                    if (matched) {
                        calibration_value_1 = pair.second - '0';
                        break;
                    }
                }
            }
            char_index++;
        }
        // REPEAT, FOR CALIBRATION VALUE 2, BUT STARTING FROM RIGHT
        char_index = line_size - 1;
        while (calibration_value_2 == -1 && char_index >= 0) {
            if (std::isdigit(line[char_index])) {
                calibration_value_2 = line[char_index] - '0';
            }
            else {
                // Loop through every key/value pair in the string:num map
                for (const auto &pair : string_num_map) {
                    int char_index_copy = char_index;
                    size_t key_size = pair.first.size();
                    int key_char_index = key_size - 1; // current index in the key string (START AT THE END THIS TIME)
                    if (char_index < key_size) {
                        continue;
                    }
                    // If space, loop thru each char in the key and compare it to the chars in the line
                    bool matched = true;
                    while (key_char_index >= 0) {
                        if (pair.first[key_char_index] != line[char_index_copy]) {
                            matched = false;
                        }
                        key_char_index--;
                        char_index_copy--;
                    }
                    if (matched) {
                        calibration_value_2 = pair.second - '0';
                        break;
                    }
                }
            }
            char_index--;
        }
        // Add the final cal value, e.g., for '7', '4', its 74
        std::cout << "Cal val 1: " << calibration_value_1 << "; Cal val 2: " << calibration_value_2 << "\n";
        std::cout << sum_of_calibration_values;
        sum_of_calibration_values += calibration_value_1 * 10 + calibration_value_2;
        std::cout << " -> " << sum_of_calibration_values << std::endl;
    }
    
    std::cout << "FINAL SUM OF CALIBRATION VALUES: " << sum_of_calibration_values << std::endl;

    return 0;
}
