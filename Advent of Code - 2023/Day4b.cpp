#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

std::set<int> convertToSet(const std::string& str) {
    std::istringstream iss(str);
    std::set<int> numbers;
    int number;
    while (iss >> number) {
        numbers.insert(number);
    }
    return numbers;
}

std::pair<std::set<int>, std::set<int>> parseCard(const std::string& line) {
    auto delimiterPos = line.find('|');
    auto winningPart = line.substr(0, delimiterPos);
    auto yourNumbersPart = line.substr(delimiterPos + 1);
    
    auto winningNumbersStart = winningPart.find(':') + 1;
    auto winningNumbersStr = winningPart.substr(winningNumbersStart);

    std::set<int> winningNumbers = convertToSet(winningNumbersStr);
    std::set<int> yourNumbers = convertToSet(yourNumbersPart);

    return {winningNumbers, yourNumbers};
}

int calculateWins(const std::set<int>& winningNumbers, const std::set<int>& yourNumbers) {
    std::vector<int> matches;
    std::set_intersection(winningNumbers.begin(), winningNumbers.end(),
                          yourNumbers.begin(), yourNumbers.end(),
                          std::back_inserter(matches));
    return static_cast<int>(matches.size());
}

std::vector<std::pair<std::set<int>, std::set<int>>> readScratchcardsFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::vector<std::pair<std::set<int>, std::set<int>>> scratchcards;
    std::string line;
    
    while (std::getline(file, line)) {
        scratchcards.push_back(parseCard(line));
    }

    return scratchcards;
}

int processScratchcards(const std::vector<std::pair<std::set<int>, std::set<int>>>& scratchcards) {
    std::vector<size_t> cardCounts(scratchcards.size(), 1);
    for (size_t i = 0; i < scratchcards.size(); ++i) {
        if (cardCounts[i] > 0) {
            auto [winningNumbers, yourNumbers] = scratchcards[i];
            int wins = calculateWins(winningNumbers, yourNumbers);
            for (size_t j = 1; j <= static_cast<size_t>(wins); ++j) {
                if (i + j < cardCounts.size()) {
                    cardCounts[i + j] += cardCounts[i];
                }
            }
        }
    }

    size_t total = 0;
    for (size_t count : cardCounts) {
        total += count;
    }
    return static_cast<int>(total);
}

int main() {
    std::string filePath = "Day4.txt";
    try {
            auto scratchcards = readScratchcardsFromFile(filePath);
            int totalScratchcards = processScratchcards(scratchcards);
            std::cout << "Total scratchcards including copies won: " << totalScratchcards << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "An error occurred: " << e.what() << std::endl;
            return 2;
        }
    return 0;
}
