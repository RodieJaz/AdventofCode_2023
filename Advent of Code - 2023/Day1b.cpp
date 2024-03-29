#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

int digitValue(std::string word) {
    std::unordered_map<std::string, int> word_to_num = {
        {"one", 1}, {"two", 2}, {"three", 3},
        {"four", 4}, {"five", 5}, {"six", 6},
        {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    if (word_to_num.find(word) != word_to_num.end()) {
        return word_to_num[word];
    }
    return -1;
}

int calculateCalibrationValue(std::string line) {
    std::vector<std::string> digit_words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    bool first_digit_found = false;
    std::string temp_line = "";
    int first_digit = -1, last_digit = -1;

    // Find the first digit or digit word from the left
    for (char& c : line) {
        if (first_digit_found) break;
        temp_line += c;
        if (isdigit(c)) {
            first_digit = c - '0';
            first_digit_found = true;
            temp_line.clear();
        } else {
            for (auto& word : digit_words) {
                if (temp_line.find(word) != std::string::npos) {
                    first_digit = digitValue(word);
                    first_digit_found = true;
                    temp_line.clear();
                    break;
                }
            }
        }
    }

    // Find the last digit or digit word from the right
    temp_line.clear();
    for (auto it = line.rbegin(); it != line.rend(); ++it) {
        temp_line = *it + temp_line;
        if (isdigit(*it)) {
            last_digit = *it - '0';
            break;
        } else {
            for (auto& word : digit_words) {
                if (temp_line.find(word) != std::string::npos) {
                    last_digit = digitValue(word);
                    break;
                }
            }
            if (last_digit != -1) break;
        }
    }

    if (first_digit != -1 && last_digit != -1) {
        return first_digit * 10 + last_digit;
    }
    return 0;
}

int sumCalibrationValues(std::string file_path) {
    std::ifstream file(file_path);
    std::string line;
    int total_calibration_value = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            total_calibration_value += calculateCalibrationValue(line);
        }
        file.close();
    }
    return total_calibration_value;
}

int main() {
    std::string file_path = "Day1.txt";
    int total_sum = sumCalibrationValues(file_path);
    std::cout << "The sum of all calibration values is: " << total_sum << std::endl;
    return 0;
}

