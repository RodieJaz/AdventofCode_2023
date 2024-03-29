#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <iterator>

const std::string DELIMITER = "|";

int calculatePointsForLine(const std::string& line) {
    std::istringstream iss(line);
    std::set<std::string> winningNumbers;
    std::set<std::string> yourNumbers;
    std::string number;
    bool isYourNumbers = false;

    while (iss >> number) {
        if (number == DELIMITER) {
            isYourNumbers = true;
            continue;
        }
        if (!isYourNumbers) {
            winningNumbers.insert(number);
        } else {
            yourNumbers.insert(number);
        }
    }

    std::set<std::string> matches;
    std::set_intersection(winningNumbers.begin(), winningNumbers.end(),
                          yourNumbers.begin(), yourNumbers.end(),
                          std::inserter(matches, matches.begin()));

    int points = 0;
    if (!matches.empty()) {
        points = 1;
        for (auto it = std::next(matches.begin()); it != matches.end(); ++it) {
            points *= 2;
        }
    }

    return points;
}

int calculatePointsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1; // Indicates an error
    }

    int totalPoints = 0;
    std::string line;
    while (std::getline(file, line)) {
        totalPoints += calculatePointsForLine(line);
    }

    return totalPoints;
}

int main() {
    std::string filename = "Day4.txt";
    
    int totalPoints = calculatePointsFromFile(filename);
    if (totalPoints == -1) {
        return 1;
    }

    std::cout << "Total Points: " << totalPoints << std::endl;
    return 0;
}
