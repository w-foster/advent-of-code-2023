#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include <unordered_map>

#include "json.hpp"

using json = nlohmann::json;

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> rounds;
    std::stringstream ss(str);
    std::string token;

    // Use getline to split by the delimiter
    while (std::getline(ss, token, delimiter)) {
        rounds.push_back(token);
    }

    return rounds;
}


int main() {

    // Setting up a vector<string> with the lines
    std::ifstream f("day2_lines.json");
    if (!f.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return 1;
    }

    json data;
    f >> data;

    std::vector<std::string> lines = data.get<std::vector<std::string>>();
    
    // Cleaning up lines - removing 'Game X: '
    for (int i = 0; i < 9; i++) {
        lines[i].erase(0, 7);
    }
    for (int i = 9; i < 99; i++) {
        lines[i].erase(0, 8);
    }
    for (int i = 99; i < 100; i++) {
        lines[i].erase(0, 9);
    }

    // Splitting the lines into a vector of rounds
    std::vector<std::vector<std::string>> rounds_by_line;
    for (const std::string line : lines) {
        rounds_by_line.push_back(split(line, ';'));
    }

    // Splitting the rounds into vectors of num+colour strings -- e.g., "16 red"
    std::vector<std::vector<std::vector<std::string>>> colours_by_round_by_line;
    for (const auto line : rounds_by_line) {
        std::vector<std::vector<std::string>> split_line;
        for (const auto round : line) {
            split_line.push_back(split(round, ','));
        }
        colours_by_round_by_line.push_back(split_line);
    }


    int sum_of_powers = 0;
    int game = 1;
    for (auto &line : colours_by_round_by_line) {
        std::cout << "Game " << game << ": \n";
        std::unordered_map<std::string, int> highest_seen_numbers = {
            {"red", 0},
            {"green", 0},
            {"blue", 0}
        };
        for (auto &round : line) {
            std::cout << "Round: " << "\n";
            for (auto &colour : round) {
                // Remove space at start of each 'colour+num' string
                colour.erase(0, 1);
                std::cout << colour << "\n";

                std::string colour_copy = colour;
                std::vector<std::string> num_and_colour = split(colour_copy, ' ');
                std::string col = num_and_colour[1];
                int num = std::stoi(num_and_colour[0]);

                if (num > highest_seen_numbers[col]) {
                    highest_seen_numbers[col] = num;
                }
            }
        }
        int power = 1;
        for (const auto &pair : highest_seen_numbers) {
            power = power * pair.second;
        }
        sum_of_powers += power;
        std::cout << sum_of_powers << "\n\n";
        game++;
    }
    std::cout << std::endl;

    // The Elf would first like to know which games would have been possible if the bag contained only:
    // --> 12 red cubes, 13 green cubes, and 14 blue cubes?
    // E.g. Game 100: 16 red, 3 blue; 2 red, 5 green; 9 red; 1 blue, 3 green, 10 red; 1 red, 5 blue, 3 green; 12 blue, 9 red
    // NOT POSSIBLE, since Round1.red == 16, and 16 > 12

    // ANSWER: 62241

    return 0;
}