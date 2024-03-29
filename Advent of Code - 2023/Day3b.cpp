#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> readFileIntoVector(const string& filename) {
    ifstream fin(filename);
    vector<string> lines;
    string line;
    if (!fin.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        throw runtime_error("File cannot be opened.");
    }
    while (getline(fin, line)) {
        lines.push_back(line);
    }
    fin.close();
    return lines;
}

void findAdjacentNumbers(const vector<string>& lines, vector<vector<vector<int>>>& goods) {
    long n = lines.size();
    long m = lines[0].size();

    auto isSymbol = [&](int i, int j, int num) -> bool {
        if (i < 0 || i >= n || j < 0 || j >= m) return false;
        if (lines[i][j] == '*') {
            goods[i][j].push_back(num);
            return true;
        }
        return (lines[i][j] != '.' && !isdigit(lines[i][j]));
    };

    for (int i = 0; i < n; ++i) {
        int j = 0;
        while (j < m) {
            int start = j;
            string numStr = "";
            while (j < m && isdigit(lines[i][j])) {
                numStr += lines[i][j++];
            }
            if (!numStr.empty()) {
                int number = stoi(numStr);
                if (!isSymbol(i, start - 1, number) && !isSymbol(i, j, number)) {
                    for (int k = start - 1; k <= j; ++k) {
                        isSymbol(i - 1, k, number);
                        isSymbol(i + 1, k, number);
                    }
                }
            } else {
                ++j;
            }
        }
    }
}

int calculateSumOfGearRatios(const vector<vector<vector<int>>>& goods) {
    int sum = 0;
    for (const auto& row : goods) {
        for (const auto& cell : row) {
            if (cell.size() == 2) {
                sum += cell[0] * cell[1];
            }
        }
    }
    return sum;
}

int main() {
    try {
        const string filename = "Day3.txt";
        vector<string> lines = readFileIntoVector(filename);
        vector<vector<vector<int>>> goods(lines.size(), vector<vector<int>>(lines[0].size(), vector<int>()));

        findAdjacentNumbers(lines, goods);
        int sumOfGearRatios = calculateSumOfGearRatios(goods);

        cout << "Sum of all gear ratios in the engine schematic: " << sumOfGearRatios << endl;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
